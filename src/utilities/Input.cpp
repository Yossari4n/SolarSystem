#include "Input.h"

Input::Input() {
    for (int i = 0; i < GLFW_KEY_MENU + 1; ++i) {
        m_Keys[i] = KeyState::NONE;
    }
}

void Input::KeyUpdate(GLFWwindow *window) {
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
}

Input::KeyState Input::GetKeyState(int glfw_key_enum) {
    return m_Keys[glfw_key_enum];
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    static bool first_mouse = true;
    
    if (first_mouse) {
        g_Input.m_MouseX = 2880.0f / 2.0f;
        g_Input.m_MouseY = 1800.0f / 2.0f;
        first_mouse = false;
    }
    
    g_Input.m_MouseX = xpos;
    g_Input.m_MouseY = ypos;
}
