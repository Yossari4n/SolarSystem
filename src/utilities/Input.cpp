#include "Input.h"

void Input::Update(GLFWwindow *window) {
    for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_MENU + 1; ++i) {
        m_Keys[i] = glfwGetKey(m_Window, i) == GLFW_PRESS;
    }
}

bool Input::IsPressed(int glfw_key_enum) {
    return m_Keys[glfw_key_enum];
}
