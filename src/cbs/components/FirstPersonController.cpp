#include "FirstPersonController.h"

FirstPersonController::FirstPersonController(float movement_speed_fast, float movement_speed_slow, float mouse_sensivity, float yaw, float pitch, glm::vec3 world_up)
    : m_MovementSpeedFast(movement_speed_fast)
    , m_MovementSpeedSlow(movement_speed_slow)
    , m_MouseSensivity(mouse_sensivity)
    , m_Yaw(yaw)
    , m_Pitch(pitch)
    , m_WorldUp(world_up) {
}

void FirstPersonController::Initialize() {
    m_LastMousePos = g_Input.MousePosition();
    m_Transform = &Object().Transform();
}

void FirstPersonController::Update() {
    float dt = g_Time.DeltaTime();
    
    // Keyboard
    if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT)) {
        m_CurrentMovementSpeed = m_MovementSpeedFast;
    } else {
        m_CurrentMovementSpeed = m_MovementSpeedSlow;
    }
    
    if (g_Input.GetKeyState(GLFW_KEY_W) || g_Input.GetKeyState(GLFW_KEY_UP)) {
        m_Transform->Move(m_Front * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_S) || g_Input.GetKeyState(GLFW_KEY_DOWN)) {
        m_Transform->Move(-m_Front * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_A) || g_Input.GetKeyState(GLFW_KEY_LEFT)) {
        m_Transform->Move(-m_Right * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_D) || g_Input.GetKeyState(GLFW_KEY_RIGHT)) {
        m_Transform->Move(m_Right * m_CurrentMovementSpeed * dt);
    }
    
    // Mouse
    float x_rotation = glm::radians(g_Input.MouseOffset().y * m_MouseSensivity);
    float y_rotation = glm::radians(-g_Input.MouseOffset().x * m_MouseSensivity);
    
    m_Transform->Rotate(glm::vec3(x_rotation, y_rotation, 0.0f));
    
    m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_Front = Object().Transform().Rotation() * m_Front;
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
}
