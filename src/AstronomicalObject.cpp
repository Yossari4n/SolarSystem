#include "AstronomicalObject.h"

AstronomicalObject::AstronomicalObject(const std::string& name, float rotation_speed)
    : m_Name(name)
    , m_RotationSpeed(rotation_speed) {
}

AstronomicalObject::~AstronomicalObject() {}

void AstronomicalObject::Update() {
    // Spinning
    float dt = g_Time.delta_time;
    glm::vec3 curr_rotation = Rotation();
    Rotation(glm::vec3(0.0f, curr_rotation.y + m_RotationSpeed * dt, 0.0f));
    
    // Orbit calculations
    if (m_Orbit.Center != nullptr) {
        float time = g_Time.current_time;
        float pos_x = cos(time * m_Orbit.AngularVelocity) * m_Orbit.Radius + m_Orbit.Center->x;
        float pos_z = sin(time * m_Orbit.AngularVelocity) * m_Orbit.Radius + m_Orbit.Center->z;
        Position(glm::vec3(pos_x, 0.0f, pos_z));
    }
}
