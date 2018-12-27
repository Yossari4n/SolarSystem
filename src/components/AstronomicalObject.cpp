#include "AstronomicalObject.h"

AstronomicalObject::AstronomicalObject(float rotation_speed)
    : m_RotationSpeed(rotation_speed) {}

AstronomicalObject::~AstronomicalObject() {}

void AstronomicalObject::Update() {
    // Spinning
    float dt = g_Time.FixedDeltaTime();
    //glm::vec3 curr_rotation = Object().Rotation();
    //Object().Rotation(glm::vec3(-90.0f, 0, curr_rotation.z + m_RotationSpeed * dt));
    Object().Rotate(glm::vec3(0.0f, 0.0f, m_RotationSpeed * dt));
    
    // Orbit calculations
    if (m_Orbit.Center != nullptr) {
        float time = g_Time.FixedCurrentTime();
        float pos_x = cos(time * m_Orbit.AngularVelocity) * m_Orbit.Radius + m_Orbit.Center->x;
        float pos_z = sin(time * m_Orbit.AngularVelocity) * m_Orbit.Radius + m_Orbit.Center->z;
        Object().Position(glm::vec3(pos_x, 0.0f, pos_z));
    }
}
