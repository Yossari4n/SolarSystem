#include "AstronomicalObject.h"

AstronomicalObject::AstronomicalObject(const std::string& name, const glm::vec3* orbit_center, float orbit_radius, float speed)
    : m_Name(name)
    , m_OrbitCenter(orbit_center)
    , m_OrbitRadius(orbit_radius)
    , m_Speed(speed) {
}

AstronomicalObject::~AstronomicalObject() {}

void AstronomicalObject::Update() {
    if (m_OrbitCenter == nullptr) {
        return;
    }
    
    float time = g_Time.current_time;
    float pos_x = cos(time * m_Speed) * m_OrbitRadius + m_OrbitCenter->x;
    float pos_z = sin(time * m_Speed) * m_OrbitRadius + m_OrbitCenter->z;
    
    Position(glm::vec3(pos_x, 0.0f, pos_z));
}
