#include "Camera.h"

Camera::Camera(glm::mat4 projection, glm::vec3 front, glm::vec3 world_up)
    : m_Projection(projection)
    , m_Front(front)
    , m_WorldUp(world_up){
}

Camera::~Camera() {}

void Camera::Initialize() {
    Object().Scene().DrawManger().RegisterCamera(this);
}

void Camera::Update() {
    m_Position = Object().Position();
    
    //glm::vec3 rotation = glm::eulerAngles(Object().Rotation());
    //m_CurrentFront = glm::vec3(0.0f, 0.0f, -1.0f);
    //m_CurrentFront = glm::rotate(m_CurrentFront, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    //m_CurrentFront = glm::rotate(m_CurrentFront, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    //m_CurrentFront = glm::rotate(m_CurrentFront, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_CurrentFront = Object().Rotation() * m_Front;
    
    m_Right = glm::normalize(glm::cross(m_CurrentFront, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_CurrentFront));
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_CurrentFront, m_Up);
}
