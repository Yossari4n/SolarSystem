#include "Input.h"

void Input::KeyUpdate(GLFWwindow *window) {
    for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_MENU + 1; ++i) {
        m_Keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
    }
}

bool Input::IsPressed(int glfw_key_enum) {
    return m_Keys[glfw_key_enum];
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    static bool first_mouse = true;
    
    if (first_mouse) {
        g_Input.m_MouseX = xpos;
        g_Input.m_MouseY = ypos;
        first_mouse = false;
    }
    
    g_Input.m_MouseXOffset = xpos - g_Input.m_MouseX;
    g_Input.m_MouseYOffset = g_Input.m_MouseY - ypos; // reversed since y-coordinates go from bottom to top
}
