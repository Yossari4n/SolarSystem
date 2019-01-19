#ifndef Input_hpp
#define Input_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Input {
    friend void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    
public:
    Input();
    
    enum KeyState {
        NONE = 0,   // The key is not being pressed nor been
        PRESSED,    // The key is pressed in this frame
        HOLD,       // The key is still being pressed
        RELEASED,   // The key was pressed in previous frame and is not now
    };
    
    void Update(GLFWwindow *window);
    
    bool AnyKeyPressed() { return m_AnyKeyPressed; }
    Input::KeyState GetKeyState(int glfw_key_enum);
    const glm::vec2& MouseOffset() const { return m_MouseOffset; }
    const glm::vec2& MousePosition() const { return m_MousePosition; }
    
private:
    bool m_AnyKeyPressed;
    Input::KeyState m_Keys[GLFW_KEY_MENU + 1];
    
    bool m_MouseFirstMove;
    glm::vec2 m_MousePosition;
    glm::vec2 m_MouseLastPosition;
    glm::vec2 m_MouseOffset;
};

void MouseCallback(GLFWwindow* window, double xpos, double ypos);

extern Input g_Input;

#endif
