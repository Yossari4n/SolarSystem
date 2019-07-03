#ifndef AstronomicalObject_hpp
#define AstronomicalObject_hpp

#define _USE_MATH_DEFINES

#include "IComponent.h"
#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

#include <iostream>
#include <string>
#include <math.h>
#include <ctime>

class AstronomicalObject : public IComponent {
public:
	AstronomicalObject(float N1, float N2, float i1, float i2, float w1, float w2, float a1, float a2, float e1, float e2, float M1, float M2);
    
    void Update() override;

private:
	int TimeScale();
	float Rev(float x);

	std::time_t m_RawTime;
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
