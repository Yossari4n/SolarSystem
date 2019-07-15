#include "AstronomicalObject.h"

#include "MeshRenderer/MeshRenderer.h"

AstronomicalObject::AstronomicalObject(OrbitalElements orbital_elements)
	: m_RawTime(time(0))
	, m_StartingPos(0.0f)
	, m_EndPos(0.0f)
	, m_LerpTime(0.0f)
	, m_N1(orbital_elements.N1)
	, m_N2(orbital_elements.N2)
	, m_i1(orbital_elements.N2)
	, m_i2(orbital_elements.i2)
	, m_w1(orbital_elements.w1)
	, m_w2(orbital_elements.w2)
	, m_a1(orbital_elements.a1)
	, m_a2(orbital_elements.a2)
	, m_e1(orbital_elements.e1)
	, m_e2(orbital_elements.e2)
	, m_M1(orbital_elements.M1)
	, m_M2(orbital_elements.M2) {
}

void AstronomicalObject::Initialize() {
	m_StartingPos = m_EndPos = Position();
}

void AstronomicalObject::Update() {
	m_LerpTime = m_LerpTime + g_Time.DeltaTime();
	
	Object().Transform().Position(glm::lerp<float>(m_StartingPos, m_EndPos, m_LerpTime));

	if (m_LerpTime > 1.0f) {
		m_RawTime = m_RawTime + DAY_TO_SEC * static_cast<std::time_t>(g_Time.TimeMultiplayer());

		m_StartingPos = m_EndPos;
		m_EndPos = Position();

		m_LerpTime = 0.0f;
	}
}

// Implementation based on https://stjarnhimlen.se/comp/ppcomp.html
glm::vec3 AstronomicalObject::Position() const {
	const int d = TimeScale();

	float N = Rev(m_N1 + m_N2 * d);		// Longitude of the ascending node
	float i = m_i1 + m_i2 * d;			// Inclination to the ecliptic (plane of the Earth's orbit)
	float w = Rev(m_w1 + m_w2 * d);		// Argument of perihelion
	float a = m_a1 + m_a2 * d;			// Mean distance from Sun
	float e = m_e1 + m_e2 * d;			// Eccentricity (0=circle, 0-1=ellipse, 1=parabola)
	float M = Rev(m_M1 + m_M2 * d);		// Mean anomaly (0 at perihelion; increases uniformly with time)

	float E = M + e * (180.0f / M_PIf) * sin(glm::radians(M)) * (1.0f + e * cos(glm::radians(M)));	// Eccentric anomaly

	// Rectangular coordinates
	float xv = a * (cos(glm::radians(E)) - e);
	float yv = a * (sin(glm::radians(E)) * sqrt(1 - pow(e, 2)));

	float r = sqrt(pow(xv, 2) + pow(yv, 2));	// Distance
	float v = glm::degrees(atan2(xv, yv));		// True anomaly

	// Convert to radians
	float N_rad = glm::radians(N);
	float i_rad = glm::radians(i);
	float vw_rad = glm::radians(v + w);

	// Heliocentric coordinates
	glm::vec3 h_pos;
	h_pos.x = r * (cos(N_rad) * cos(vw_rad) - sin(N_rad) * sin(vw_rad) * cos(i_rad));
	h_pos.y = r * sin(i_rad) * sin(vw_rad);
	h_pos.z = r * (sin(N_rad) * cos(vw_rad) + cos(N_rad) * sin(vw_rad) * cos(i_rad));
	h_pos = h_pos * ASTRONOMICAL_UNIT;

	return h_pos;
}

int AstronomicalObject::TimeScale() const {
	std::tm date;
	localtime_s(&date, &m_RawTime);

	const int Y = date.tm_year + 1900;
	const int M = date.tm_mon + 1;
	const int D = date.tm_mday;

	return 367 * Y - (7 * (Y + ((M + 9) / 12))) / 4 + (275 * M) / 9 + D - 730530;
}

#undef _USE_MATH_DEFINES