#ifndef Input_hpp
#define Input_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Input {
    friend void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    
public:
    void KeyUpdate(GLFWwindow *window);
    void MouseUpdate(GLFWwindow *window);
    
    bool IsPressed(int glfw_key_enum);
    glm::vec2 MousePosition() const { return glm::vec2(m_MouseX, m_MouseY); }
    glm::vec2 MouseOffset() const { return glm::vec2(m_MouseXOffset, m_MouseYOffset); }
    
private:
    int m_Keys[GLFW_KEY_MENU + 1];
    
    float m_MouseX, m_MouseY;
    float m_MouseXOffset, m_MouseYOffset;
};

void MouseCallback(GLFWwindow* window, double xpos, double ypos);

extern Input g_Input;

#endif
