#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL

#include "cbs/components/MeshRenderer/MeshRenderer.h"
#include "cbs/components/Camera.h"
#include "utilities/Time.h"
#include "utilities/Input.h"
#include "scenes/MainScene.h"

// Screen setting
const int SCR_WIDTH = 2880;
const int SCR_HEIGHT = 1800;

// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Global objects
Time g_Time;
Input g_Input;

int main() {
    // Initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create window
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SolarSystem", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window\n";
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    
    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, MouseCallback);
    
    // Capture the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Main scene
    MainScene MainScene;
    MainScene.CreateScene();
    
    // Render settings
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    MainScene.PreRun();
    
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        g_Time.Update();
        g_Input.Update(window);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        MainScene.Run();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // End of application
    MainScene.PostRun();
    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
