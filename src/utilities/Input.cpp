#include "Input.h"

Input::Input() {
    m_MousePosition.x = 2880.0f / 2.0f;
    m_MousePosition.y = 1800.0f / 2.0f;
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
}

Input::KeyState Input::GetKeyState(int glfw_key_enum) {
    return m_Keys[glfw_key_enum];
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    g_Input.m_MousePosition.x = xpos;
    g_Input.m_MousePosition.y = ypos;
}
