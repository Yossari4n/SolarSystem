#include "Camera.h"

#undef far
#undef near

Camera::Camera(glm::mat4 projection)
    : m_Projection(projection)  {
}

Camera::Camera(float fovy, float aspect, float near, float far) {
    Perspective(fovy, aspect, near, far);
}

Camera::Camera(float left, float right, float bottom, float top, float near, float far) {
    Orthographic(left, right, bottom, top, near, far);
}

void Camera::Initialize() {
    Object().Scene().RegisterCamera(this);
    m_Transform = &Object().Transform();
}

void Camera::Perspective(float fovy, float aspect, float near, float far) {
    m_Projection = glm::perspective(fovy, aspect, near, far);
}

void Camera::Orthographic(float left, float right, float bottom, float top, float near, float far) {
    m_Projection = glm::ortho(left, right, bottom, top, near, far);
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Transform->Position(),
                       m_Transform->Position() + m_Transform->Front(),
                       m_Transform->Up());
}
