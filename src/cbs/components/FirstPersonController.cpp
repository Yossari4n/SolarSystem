#include "FirstPersonController.h"

FirstPersonController::FirstPersonController(float movement_speed_fast, float movement_speed_slow, float mouse_sensivity, glm::vec3 front, glm::vec3 world_up)
    : m_MovementSpeedFast(movement_speed_fast)
    , m_MovementSpeedSlow(movement_speed_slow)
    , m_MouseSensitivity(mouse_sensivity)
    , m_Front(front)
    , m_WorldUp(world_up) {
    
}

void FirstPersonController::Initialize() {
    m_LastMousePos = g_Input.MousePosition();
    m_Transform = &Object().Transform();
}

void FirstPersonController::Update() {
    float dt = g_Time.DeltaTime();
    
    // Mouse
    float x_rotation = glm::radians(g_Input.MouseOffset().y * m_MouseSensitivity);
    float y_rotation = glm::radians(-g_Input.MouseOffset().x * m_MouseSensitivity);
    
    m_Transform->Rotate(glm::vec3(x_rotation, y_rotation, 0.0f));
    
    glm::vec3 curr_front = m_Front;
    curr_front = m_Transform->Rotation() * curr_front;
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    
    // Keyboard
    if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT)) {
        m_CurrentMovementSpeed = m_MovementSpeedFast;
    } else {
        m_CurrentMovementSpeed = m_MovementSpeedSlow;
    }
    
    if (g_Input.GetKeyState(GLFW_KEY_W) || g_Input.GetKeyState(GLFW_KEY_UP)) {
        m_Transform->Move(curr_front * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_S) || g_Input.GetKeyState(GLFW_KEY_DOWN)) {
        m_Transform->Move(-curr_front * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_A) || g_Input.GetKeyState(GLFW_KEY_LEFT)) {
        m_Transform->Move(-m_Right * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_D) || g_Input.GetKeyState(GLFW_KEY_RIGHT)) {
        m_Transform->Move(m_Right * m_CurrentMovementSpeed * dt);
    }
}
