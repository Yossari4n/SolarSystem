#ifndef AstronomicalObject_hpp
#define AstronomicalObject_hpp

#define _USE_MATH_DEFINES

#include "IComponent.h"
#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#pragma warning(pop)

#include <iostream>
#include <string>
#include <math.h>
#include <ctime>

constexpr float M_PIf = static_cast<float>(M_PI);
constexpr float ASTRONOMICAL_UNIT = 150.0f / 3.0f;
constexpr time_t DAY_TO_SEC = 60 * 60 * 24;

struct OrbitalElements {
	OrbitalElements(float N1, float N2, float i1, float i2, float w1, float w2, float a1, float a2, float e1, float e2, float M1, float M2)
		: N1(N1)
		, N2(N2)
		, i1(i1)
		, i2(i2)
		, w1(w1)
		, w2(w2)
		, a1(a1)
		, a2(a2)
		, e1(e1)
		, e2(e2)
		, M1(M1)
		, M2(M2) {
	}

	// Longitude of the ascending node
	float N1;
	float N2;
	// Inclination to the ecliptic (plane of the Earth's orbit)
	float i1;
	float i2;
	// Argument of perihelion
	float w1;
	float w2;
	// Semi-major axis, or mean distance from Sun
	float a1;
	float a2;
	// Eccentricity(0 = circle, 0 - 1 = ellipse, 1 = parabola)
	float e1;
	float e2;
	// Mean anomaly
	float M1;
	float M2;
};

class AstronomicalObject : public IComponent {
public:
	AstronomicalObject(OrbitalElements orbital_elements);
    
	void Initialize() override;
    void Update() override;

private:
	glm::vec3 Position() const;
	int TimeScale() const;

	float Rev(float x) const {
		return x - floor(x / 360.0f) * 360.0f;
	}

	std::time_t m_RawTime;

	// Positions for lerp
	float m_LerpTime;
	glm::vec3 m_StartingPos;
	glm::vec3 m_EndPos;

	// Orbital elements
	float m_N1;
	float m_N2;
	float m_i1;
	float m_i2;
	float m_w1;
	float m_w2;
	float m_a1;
	float m_a2;
	float m_e1;
	float m_e2;
	float m_M1;
	float m_M2;
};

#endif
