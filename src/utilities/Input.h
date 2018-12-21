#ifndef Input_hpp
#define Input_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Input {
public:
    void Update(GLFWwindow *window);
    
    bool IsPressed(int glfw_key_enum);
    
    GLFWwindow* m_Window;
    
private:
    int m_Keys[GLFW_KEY_MENU + 1];
};

extern Input g_Input;

#endif
