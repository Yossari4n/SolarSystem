#ifndef AstronomicalObject_hpp
#define AstronomicalObject_hpp

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>

#include "IComponent.h"
#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

struct Orbit {
    Orbit(const glm::vec3* center = nullptr, float radius = 0, float angular_velocity = 0)
        : Center(center)
        , Radius(radius)
        , AngularVelocity(angular_velocity) {
        }
    
    const glm::vec3* Center;
    float Radius;
    float AngularVelocity;
};

class AstronomicalObject : public IComponent {
public:
    AstronomicalObject(float rotation_speed = 0);
    
    void Initialize() override;
    void Update() override;
    
    const Orbit& Orbit() const { return m_Orbit; }
    void Orbit(struct Orbit orbit) { m_Orbit = orbit; }

private:
    float m_RotationSpeed;
    struct Orbit m_Orbit;
};

#endif
