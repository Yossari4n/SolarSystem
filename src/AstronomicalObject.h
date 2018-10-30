#ifndef AstronomicalObject_hpp
#define AstronomicalObject_hpp

#include <string>

#include "Sphere.h"

class AstronomicalObject: public Sphere {
public:
    AstronomicalObject(const std::string& name = "", const glm::vec3* orbit_center = nullptr, float orbit_radius = 0, float speed = 0);
    ~AstronomicalObject();
    
    void Update();
    
private:
    std::string m_Name;
    
    const glm::vec3* m_OrbitCenter;
    float m_OrbitRadius;
    float m_Speed;
};

#endif
