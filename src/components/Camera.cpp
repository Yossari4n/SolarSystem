#include "Camera.h"

Camera::Camera(glm::mat4 projection, glm::vec3 world_up)
    : m_Projection(projection)
    , m_WorldUp(world_up){
}

Camera::~Camera() {}

void Camera::Initialize() {
    Object().Scene().DrawManger().RegisterCamera(this);
}

void Camera::Update() {
    m_Position = Object().Position();
    
    glm::vec3 rotation = glm::eulerAngles(Object().Rotation());
    
    m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_Front = glm::rotate(m_Front, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_Front = glm::rotate(m_Front, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    m_Front = glm::rotate(m_Front, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}
