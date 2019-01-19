#include "Camera.h"

Camera::Camera(glm::mat4 projection, glm::vec3 front, glm::vec3 world_up)
    : m_Projection(projection)
    , m_Front(front)
    , m_WorldUp(world_up)
    , m_Background(glm::vec3(0.0f, 0.0f, 0.0f)) {
    
}

Camera::~Camera() {}

void Camera::Initialize() {
    Object().Scene().DrawManger().RegisterCamera(this);
    m_Transform = &Object().Transform();
}

void Camera::Update() {
    m_Position = m_Transform->Position();
    m_CurrentFront = m_Transform->Rotation() * m_Front;
    m_Right = glm::normalize(glm::cross(m_CurrentFront, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_CurrentFront));
}

void Camera::Destroy() {
    // unregister
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_CurrentFront, m_Up);
}
