#ifndef Input_hpp
#define Input_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Input {
    friend void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
    friend void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
    
public:
    Input();
    
    enum KeyState {
        NONE = 0,   // The key is not being pressed nor been
        PRESSED,    // The key is pressed in this frame
        HOLD,       // The key is still being pressed
        RELEASED,   // The key was pressed in previous frame and is not now
    };
    
    void Update(GLFWwindow *window);
    
    bool AnyKeyPressed() const { return m_AnyKeyPressed; }
    bool AnyKeyHold() const { return m_AnyKeyHold; }
    bool AnyKeyReleased() const { return m_AnyKeyReleased; }
    Input::KeyState GetKeyState(int glfw_key_enum) const;
    const glm::vec2& MousePosition() const { return m_MousePosition; }
    const glm::vec2& MouseOffset() const { return m_MouseOffset; }
    float ScrollOffset() const { return m_ScrollOffset; }
    
private:
    bool m_AnyKeyPressed;
    bool m_AnyKeyHold;
    bool m_AnyKeyReleased;
    Input::KeyState m_Keys[GLFW_KEY_MENU + 1];
    
    bool m_MouseFirstMove;
    bool m_ScrollChanged;
    float m_ScrollOffset;
    glm::vec2 m_MousePosition;
    glm::vec2 m_MouseLastPosition;
    glm::vec2 m_MouseOffset;
};

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void scroll_callback(GLFWwindow* window, double x_pos, double y_pos);

extern Input g_Input;

#endif
