#include "Camera.h"

#include <iostream>

Camera::Camera(glm::mat4 projection, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_Projection(projection)
    , m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
    , m_MovementSpeed(SPEED)
    , m_MouseSensitivity(SENSITIVITY)
    , m_Zoom(ZOOM)
    , m_Position(position)
    , m_WorldUp(up)
    , m_Yaw(yaw)
    , m_Pitch(pitch) {
    
    Update();
}

Camera::Camera(glm::mat4 projection, float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
    : m_Projection(projection)
    , m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
    , m_MovementSpeed(SPEED)
    , m_MouseSensitivity(SENSITIVITY)
    , m_Zoom(ZOOM) {
    m_Position = glm::vec3(pos_x, pos_y, pos_z);
    m_WorldUp = glm::vec3(up_x, up_y, up_z);
    this->m_Yaw = yaw;
    this->m_Pitch = pitch;
    
    Update();
}

Camera::~Camera() {}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::Position(const glm::vec3 &position) {
    m_Position = position;
}

void Camera::Front(const glm::vec3 &front) {
    m_Front = front;
    Update();
}

void Camera::Up(const glm::vec3 &up) {
    m_Up = up;
    Update();
}

void Camera::Right(const glm::vec3 &right) {
    m_Right = right;
    Update();
}

void Camera::WorldUp(const glm::vec3 &world_up) {
    m_WorldUp = world_up;
    Update();
}

void Camera::Yaw(const float &yaw) {
    m_Yaw = yaw;
    Update();
}

void Camera::Pitch(const float &pitch) {
    m_Pitch = pitch;
    Update();
}

void Camera::MovementSpeed(const float &movement_speed) {
    m_MovementSpeed = movement_speed > 0 ? movement_speed : 0;
}

void Camera::MouseSensitivity(const float &mouse_sensitivity) {
    m_MouseSensitivity = mouse_sensitivity > 0 ? mouse_sensitivity : 0;
}

void Camera::Zoom(const float &zoom) {
    m_Zoom = zoom;
}

void Camera::ProcessKeyboard(CameraMovement direction, float delta_time) {
    float velocity = m_MovementSpeed * delta_time;
    
    if (direction == CameraMovement::FORWARD) {
        m_Position += m_Front * velocity;
    } else if (direction == CameraMovement::BACKWARD) {
        m_Position -= m_Front * velocity;
    }
    
    if (direction == CameraMovement::LEFT) {
        m_Position -= m_Right * velocity;
    } else if (direction == CameraMovement::RIGHT) {
        m_Position += m_Right * velocity;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrain_pitch) {
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;
    
    m_Yaw += xoffset;
    m_Pitch += yoffset;
    
    // Prevent screen flipping when pitch out of bounds
    if (constrain_pitch) {
        // Keep pitch in range of (-89, 89)
        m_Pitch = m_Pitch > 89.0f ? 89.0f : m_Pitch < -89.0f ? -89.0f : m_Pitch;
    }
    
    Update();
}

void Camera::ProcessMouseScroll(float y_offset) {
    if (m_Zoom >= 1.0f && m_Zoom <= 45.0f) {
        m_Zoom -= y_offset;
    }
    
    // Keep zoom in range of <1, 45>
    m_Zoom = m_Zoom <= 1.0f ? 1.0f : m_Zoom >= 45.0f ? 45.0f : m_Zoom;
}

void Camera::Update() {
    // recalculate front vector
    m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front.y = sin(glm::radians(m_Pitch));
    m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(m_Front);
    
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
