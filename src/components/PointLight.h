#ifndef PointLight_hpp
#define PointLight_hpp

#include <glm/glm.hpp>

#include "IComponent.h"

class PointLight : public IComponent {
public:
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, float constant, float linear, float quadratic);
    
    void Initialize() override {}
    void Destroy() override {}
    
    const glm::vec3& Ambient() const { return m_Ambient; }
    void Ambient(const glm::vec3& ambient) { m_Ambient = ambient; }
    
    const glm::vec3& Diffuse() const { return m_Diffuse; }
    void Diffuse(const glm::vec3& diffuse) { m_Diffuse = diffuse; }
    
    const float& Constant() const { return m_Constant; }
    void Constant(float constant);
    
    const float& Linear() const { return m_Linear; }
    void Linear(float linear);
    
    const float& Quadratic() const { return m_Quadratic; }
    void Quadratic(float quadratic);
    
private:
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    
    float m_Constant;
    float m_Linear;
    float m_Quadratic;
};

#endif
