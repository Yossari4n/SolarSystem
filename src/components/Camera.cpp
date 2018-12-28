#include "Camera.h"

Camera::Camera(glm::mat4 projection, glm::vec3 front, glm::vec3 world_up)
    : m_Projection(projection)
    , m_Front(front)
    , m_WorldUp(world_up) {
}

Camera::~Camera() {}

void Camera::Initialize() {
    Object().Scene().DrawManger().RegisterCamera(this);
    
    UpdateAttributes();
}

void Camera::Update() {
    UpdateAttributes();
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_CurrentFront, m_Up);
}

void Camera::Front(const glm::vec3& front) {
    m_Front = front;
    UpdateAttributes();
}

void Camera::WorldUp(const glm::vec3& world_up) {
    m_WorldUp = world_up;
    UpdateAttributes();
}

void Camera::UpdateAttributes() {
    m_Position = Object().Position();
    
    m_CurrentFront = m_Front;
    m_CurrentFront = glm::rotate(m_CurrentFront, Object().Rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_CurrentFront = glm::rotate(m_CurrentFront, Object().Rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    m_CurrentFront = glm::rotate(m_CurrentFront, Object().Rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    
    m_Right = glm::normalize(glm::cross(m_CurrentFront, m_WorldUp));
    
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
