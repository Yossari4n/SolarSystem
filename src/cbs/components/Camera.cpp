#include "Camera.h"

#include "../../utilities/Line.h"

Camera::Camera(glm::mat4 projection, glm::vec3 front, glm::vec3 world_up)
    : m_Projection(projection)
    , m_Front(front)
    , m_WorldUp(world_up) {
        m_CurrentRight = glm::normalize(glm::cross(m_Front, m_WorldUp));
}

Camera::~Camera() {
}

void Camera::Initialize() {
    Object().Scene().DrawManager().RegisterCamera(this);
    m_Transform = &Object().Transform();
}

void Camera::Update() {
    m_Position = m_Transform->Position();
    
    const glm::quat& rotation = m_Transform->Rotation();
    m_CurrentFront = rotation * m_Front;
    m_Right = rotation * m_CurrentRight; //glm::normalize(glm::cross(m_CurrentFront, m_WorldUp));
    m_Up = rotation * m_WorldUp; //glm::normalize(glm::cross(m_Right, m_CurrentFront));
}

void Camera::Destroy() {
    // unregister
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_CurrentFront, m_Up);
}
