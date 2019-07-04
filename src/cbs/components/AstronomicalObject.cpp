#include "AstronomicalObject.h"

#include "MeshRenderer/MeshRenderer.h"

AstronomicalObject::AstronomicalObject(float N1, float N2, float i1, float i2, float w1, float w2, float a1, float a2, float e1, float e2, float M1, float M2)
	: m_RawTime(time(0))
	, m_N1(N1)
	, m_N2(N2)
	, m_i1(N2)
	, m_i2(i2)
	, m_w1(w1)
	, m_w2(w2)
	, m_a1(a1)
	, m_a2(a2)
	, m_e1(e1)
	, m_e2(e2)
	, m_M1(M1)
	, m_M2(M2) {
}

// Implementation based on https://stjarnhimlen.se/comp/ppcomp.html
void AstronomicalObject::Update() {
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

	Object().Transform().Position(h_pos);
}

int AstronomicalObject::TimeScale() {
	std::tm date;
	localtime_s(&date, &m_RawTime);

	const int Y = date.tm_year + 1900;
	const int M = date.tm_mon + 1;
	const int D = date.tm_mday;
	
	return 367 * Y - (7 * (Y + ((M + 9) / 12))) / 4 + (275 * M) / 9 + D - 730530;
}

#undef _USE_MATH_DEFINES