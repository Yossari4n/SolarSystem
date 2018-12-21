#include "PointLight.h"

PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, float constant, float linear, float quadratic)
    : m_Ambient(ambient)
    , m_Diffuse(diffuse)
    , m_Constant(constant)
    , m_Linear(linear)
    , m_Quadratic(quadratic) {
    m_Constant = m_Constant <= 0 ? 0.0000001f : m_Constant;
    m_Linear = m_Linear <= 0 ? 0.0000001f : m_Linear;
    m_Quadratic = m_Quadratic <= 0 ? 0.0000001f : m_Quadratic;
}

void PointLight::Constant(float constant) {
    if (constant <= 0) {
        constant = 0.0000001f;
    }
    
    m_Constant = constant;
}

void PointLight::Linear(float linear) {
    if (linear <= 0) {
        linear = 0.0000001f;
    }
    
    m_Linear = linear;
}

void PointLight::Quadratic(float quadratic) {
    if (quadratic <= 0) {
        quadratic = 0.0000001f;
    }
    
    m_Quadratic = quadratic;
}
