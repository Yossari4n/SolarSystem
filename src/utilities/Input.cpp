#include "Input.h"

Input::Input() {
    m_AnyKeyPressed = false;
    m_MouseFirstMove = true;
    
    m_MousePosition.x = 2880.0f / 2.0f;
    m_MousePosition.y = 1800.0f / 2.0f;
    m_MouseLastPosition = m_MousePosition;
    m_MouseOffset.x = 0.0f;
    m_MouseOffset.y = 0.0f;
    
    for (int i = 0; i < GLFW_KEY_MENU + 1; ++i) {
        m_Keys[i] = KeyState::NONE;
    }
}

void Input::Update(GLFWwindow *window) {
    m_AnyKeyPressed = false;
    
    for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_MENU + 1; ++i) {
        if (glfwGetKey(window, i) == GLFW_PRESS) {
            if (m_Keys[i] == KeyState::NONE || m_Keys[i] == KeyState::RELEASED) {
                m_Keys[i] = KeyState::PRESSED;
            } else if (m_Keys[i] == KeyState::PRESSED) {
                m_Keys[i] = KeyState::HOLD;
            }
            
            m_AnyKeyPressed = true;
        } else {
            if (m_Keys[i] == KeyState::PRESSED || m_Keys[i] == KeyState::HOLD) {
                m_Keys[i] = KeyState::RELEASED;
            } else {
                m_Keys[i] = KeyState::NONE;
            }
        }
    }
    
    m_MouseOffset.x = m_MousePosition.x - m_MouseLastPosition.x;
    m_MouseOffset.y = m_MouseLastPosition.y - m_MousePosition.y;
    
    m_MouseLastPosition = m_MousePosition;
}

Input::KeyState Input::GetKeyState(int glfw_key_enum) {
    return m_Keys[glfw_key_enum];
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    g_Input.m_MousePosition.x = xpos;
    g_Input.m_MousePosition.y = ypos;
    
    // Executed only once at the beginning
    if (g_Input.m_MouseFirstMove) {
        g_Input.m_MouseLastPosition = g_Input.m_MousePosition;
        g_Input.m_MouseFirstMove = false;
    }
}
