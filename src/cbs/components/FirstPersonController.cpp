#include "FirstPersonController.h"

FirstPersonController::FirstPersonController(float movement_speed_fast, float movement_speed_slow, float mouse_sensivity, glm::vec3 front, glm::vec3 world_up)
    : m_MovementSpeedFast(movement_speed_fast)
    , m_MovementSpeedSlow(movement_speed_slow)
    , m_MouseSensitivity(mouse_sensivity)
    , m_Front(front)
    , m_WorldUp(world_up) {
    m_XRotation = 0.0f;
}

void FirstPersonController::Initialize() {
    m_LastMousePos = g_Input.MousePosition();
    m_Transform = &Object().Transform();
}

void FirstPersonController::OnActivate() {
    glm::vec3 curr_front = m_Front * Object().Transform().Rotation();
    glm::vec3 projected_front(curr_front.x, 0.0f, curr_front.z); // curr_front vector projected onto XY plane
    
    m_XRotation = glm::angle(glm::normalize(curr_front), glm::normalize(projected_front));
    
    // Becouse glm::angle always returns positive value angle needs to be negated manually
    if (curr_front.y > 0.0f) {
        m_XRotation = -m_XRotation;
    }
}

void FirstPersonController::Update() {
    if (!m_Active) {
        return;
    }
    
    // Mouse
    float x_rotation = glm::radians(g_Input.MouseOffset().y * m_MouseSensitivity);
    float y_rotation = glm::radians(-g_Input.MouseOffset().x * m_MouseSensitivity);
    m_XRotation += x_rotation;
    
    // Prevent object flip
    if (m_XRotation > DEGREES_60) {
        m_XRotation = DEGREES_60;
        x_rotation = 0.0f;
    } else if (m_XRotation < -DEGREES_60) {
        m_XRotation = -DEGREES_60;
        x_rotation = 0.0f;
    }
    
    // Update vectors
    glm::vec3 curr_front = m_Transform->Rotation() * m_Front;
    m_Transform->Rotate(glm::vec3(x_rotation, y_rotation, 0.0f));
    m_Right = glm::normalize(glm::cross(curr_front, m_WorldUp));
    
    // Keyboard
    if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT)) {
        m_CurrentMovementSpeed = m_MovementSpeedFast;
    } else {
        m_CurrentMovementSpeed = m_MovementSpeedSlow;
    }
    
    float dt = g_Time.DeltaTime();
    if (g_Input.GetKeyState(GLFW_KEY_W)) {
        m_Transform->Move(curr_front * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_S)) {
        m_Transform->Move(-curr_front * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_A)) {
        m_Transform->Move(-m_Right * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_D)) {
        m_Transform->Move(m_Right * m_CurrentMovementSpeed * dt);
    }
}
