#include "Camera.h"

Camera::Camera(glm::mat4 projection, glm::vec3 front, glm::vec3 world_up)
    : m_Projection(projection)
    , m_Front(front)
    , m_WorldUp(world_up) {
}

void Camera::Initialize() {
    Object().Scene().DrawManager().RegisterCamera(this);
    m_Transform = &Object().Transform();
}

void Camera::Update() {
    m_Position = m_Transform->Position();
    
    const glm::quat& rotation = m_Transform->Rotation();
    m_CurrentFront = rotation * m_Front;
    m_Up = rotation * m_WorldUp;
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_CurrentFront, m_Up);
}
