#ifndef AstronomicalObject_hpp
#define AstronomicalObject_hpp

#include <string>

#include "Sphere.h"

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

class AstronomicalObject: public Sphere {
public:
    AstronomicalObject(const std::string& name = "", float rotation_speed = 0);
    ~AstronomicalObject();
    
    void Update();
    
    const Orbit& Orbit() const { return m_Orbit; }
    void Orbit(const struct Orbit& orbit) { m_Orbit = orbit; }
    
private:
    std::string m_Name;
    float m_RotationSpeed;
    
    struct Orbit m_Orbit;
};

#endif
