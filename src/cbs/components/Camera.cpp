#include "Camera.h"

Camera::Camera(glm::mat4 projection)
    : m_Projection(projection)  {
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
