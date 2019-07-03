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

void AstronomicalObject::Update() {
	static constexpr float M_PIf = static_cast<float>(M_PI);

	const int d = TimeScale();

	float N = m_N1 + m_N2 * d;			// Longitude of the ascending node
	float i = m_i1 + m_i2 * d;			// Inclination to the ecliptic (plane of the Earth's orbit)
	float w = m_w1 + m_w2 * d;			// Argument of perihelion
	float a = m_a1 + m_a2 * d;			// Mean distance from Sun
	float e = m_e1 + m_e2 * d;			// Eccentricity (0=circle, 0-1=ellipse, 1=parabola)
	float M = Rev(m_M1 + m_M2 * d);		// Mean anomaly (0 at perihelion; increases uniformly with time)

	float oblecl = 23.4393f - 3.563E-7f * d;	// Obliquity of the ecliptic
	float L = w + M;							// Mean longitude

	float E = M + (180.0f / M_PIf) * e * sin(M) * (1.0f + e * cos(M));	// Eccentric anomaly

	// Rectangular coordinates
	float xv = a * (cos(E) - e);
	float yv = a * (sin(E) * sqrt(1 - pow(e, 2)));

	float r = sqrt(pow(xv, 2) + pow(yv, 2));	// Distance
	float v = atan2(yv, xv);					// True anomaly

	// Heliocentric coordinates
	glm::vec3 h_pos;
	h_pos.x = r * (cos(N) * cos(v + w) - sin(N) * sin(v + w) * cos(i)) * 40.0f;
	h_pos.z = r * (sin(N) * cos(v + w) + cos(N) * sin(v + w) * cos(i)) * 40.0f;
	h_pos.y = r * (sin(v + w) * sin(i));

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

float AstronomicalObject::Rev(float angle) {
	return  angle - floor(angle / 360.0f) * 360.0f;
}

#undef _USE_MATH_DEFINES