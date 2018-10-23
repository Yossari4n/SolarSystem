#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class CameraMovement {
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW  = -90.0f;
const float PITCH = 0.0f;
const float SPEED  = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);
    ~Camera();
    
    glm::mat4 ViewMatrix();
    
    const glm::vec3& Position() const { return m_Position; }
    void Position(const glm::vec3& position);
    
    const glm::vec3& Front() const {return m_Front; }
    void Front(const glm::vec3& front);
    
    const glm::vec3& Up() const { return m_Up; }
    void Up(const glm::vec3& up);
    
    const glm::vec3& Right() const { return m_Right; }
    void Right(const glm::vec3& right);
    
    const glm::vec3& WorldUp() const { return m_WorldUp; }
    void WorldUp(const glm::vec3& world_up);
    
    const float& Yaw() const { return m_Yaw; }
    void Yaw(const float& yaw);
    
    const float& Pitch() const { return m_Pitch; }
    void Pitch(const float& pitch);
    
    const float& MovementSpeed() const { return m_MovementSpeed; }
    void MovementSpeed(const float& movement_speed);
    
    const float& MouseSensitivity() const { return m_MouseSensitivity; }
    void MouseSensitivity(const float& mouse_sensitivity);
    
    const float& Zoom() const { return m_Zoom; }
    void Zoom(const float& zoom);
    
    void ProcessKeyboard(CameraMovement direction, float delta_time);
    void ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch = true);
    void ProcessMouseScroll(float y_offset);
    
private:
    // Camera Attributes
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;
    
    // Euler Angles
    float m_Yaw;
    float m_Pitch;
    
    // Camera options
    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;
    
    glm::mat4 m_ViewMatrix;
    
    void Update();
};
