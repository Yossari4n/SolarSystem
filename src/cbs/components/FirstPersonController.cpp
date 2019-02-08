#include "FirstPersonController.h"

#include "../../utilities/Line.h"

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
    glm::vec3 curr_front = Object().Transform().Rotation() * m_Front;
    glm::vec3 projected_front(curr_front.x, 0.0f, curr_front.z); // curr_front vector projected onto XY plane
    
    m_XRotation = glm::angle(glm::normalize(curr_front), glm::normalize(projected_front));
    
    // Becouse glm::angle always returns positive value angle needs to be negated manually
    if (curr_front.y < 0.0f) {
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
    
    if (g_Input.GetKeyState(GLFW_KEY_DOWN)) {
        x_rotation -= 0.01f;
    } else if (g_Input.GetKeyState(GLFW_KEY_UP)) {
        x_rotation += 0.01f;
    }
    if (g_Input.GetKeyState(GLFW_KEY_RIGHT)) {
        y_rotation += 0.01f;
    } else if (g_Input.GetKeyState(GLFW_KEY_LEFT)) {
        y_rotation -= 0.01f;
    }
    
    
    m_XRotation += x_rotation;
    // Prevent object flip
    /*if (m_XRotation > DEGREES_60) {
        m_XRotation = DEGREES_60;
        x_rotation = 0.0f;
    } else if (m_XRotation < -DEGREES_60) {
        m_XRotation = -DEGREES_60;
        x_rotation = 0.0f;
    }*/
    
    // Update vectors
    glm::vec3 curr_front = m_Transform->Rotation() * m_Front;
    m_Transform->Rotate(glm::vec3(0.0f, y_rotation, 0.0f), Transform::WORLD);
    m_Transform->Rotate(glm::vec3(x_rotation, 0.0f, 0.0f), Transform::LOCAL);
    m_Right = m_Transform->Rotation() * glm::vec3(1.0f, 0.0f, 0.0f); //glm::normalize(glm::cross(curr_front, m_WorldUp));
    
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
    
    if (g_Input.GetKeyState(GLFW_KEY_Z) == Input::PRESSED) {
        glm::vec3 m_Position = Object().Transform().Position();
        glm::vec3 m_Up = glm::normalize(glm::cross(m_Right, curr_front));
        Line* line1 = new Line(m_Position, curr_front * 50.0f + m_Position, glm::vec3(0.0f, 1.0f, 0.0f));
        Line* line2 = new Line(m_Position, m_Right * 50.0f + m_Position, glm::vec3(1.0f, 0.0f, 0.0f));
        Line* line3 = new Line(m_Position, m_Up * 50.0f + m_Position, glm::vec3(0.0f, 0.0f, 1.0f));
        Object().Scene().DrawManager().RegsiterDrawCall(line1);
        Object().Scene().DrawManager().RegsiterDrawCall(line2);
        Object().Scene().DrawManager().RegsiterDrawCall(line3);
    }
}
