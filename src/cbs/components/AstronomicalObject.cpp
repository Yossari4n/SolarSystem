#include "AstronomicalObject.h"

#include "MeshRenderer/MeshRenderer.h"

AstronomicalObject::AstronomicalObject(float rotation_speed)
    : m_RotationSpeed(rotation_speed) {
        
}

void AstronomicalObject::Initialize() {
    if (m_Orbit.Center != nullptr) {
        float time = g_Time.FixedCurrentTime();
        float pos_x = cos(time * m_Orbit.AngularVelocity) * m_Orbit.Radius + m_Orbit.Center->x;
        float pos_z = sin(time * m_Orbit.AngularVelocity) * m_Orbit.Radius + m_Orbit.Center->z;
        Object().Transform().Position(glm::vec3(pos_x, 0.0f, pos_z));
    }
}

void AstronomicalObject::Update() {
    // Spinning
    float dt = g_Time.FixedDeltaTime();
    glm::quat rotation(glm::vec3(0.0f, 0.0f, glm::radians(m_RotationSpeed * dt)));
    Object().Transform().Rotate(rotation);
    
    // Orbit calculations
    if (m_Orbit.Center != nullptr) {
        float time = g_Time.FixedCurrentTime();
        float pos_x = cos(time * m_Orbit.AngularVelocity) * m_Orbit.Radius + m_Orbit.Center->x;
        float pos_z = sin(time * m_Orbit.AngularVelocity) * m_Orbit.Radius + m_Orbit.Center->z;
        Object().Transform().Position(glm::vec3(pos_x, 0.0f, pos_z));
    }
}
