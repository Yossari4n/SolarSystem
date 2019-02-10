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

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Transform->Position(),
                       m_Transform->Position() + m_Transform->Front(),
                       m_Transform->Up());
}
