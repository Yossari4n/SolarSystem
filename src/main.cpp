#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include "components/MeshRenderer/MeshRenderer.h"
#include "utilities/Time.h"
#include "utilities/Input.h"
#include "scenes/Scene.h"
#include "Camera.h"

// Screen setting
const int SCR_WIDTH = 2880;
const int SCR_HEIGHT = 1800;

// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);

// Input functions
void process_input(GLFWwindow *window);

// Global objects
Camera g_Camera(glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5000.0f),
                glm::vec3(-5.0f, 20.0f, 5.0f),
                glm::vec3(0.0f, 1.0f, 0.0f),
                -30.0f,
                -30.0f);
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
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    g_Input.m_Window = window;
    
    // Capture the mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }
    
    // Main scene
    Scene MainScene;
    MainScene.Initialize();
    
    // Render settings
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PRIMITIVE_RESTART_INDEX);
    
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        g_Time.Update();
        g_Input.Update(window);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        process_input(window);
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

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    // Exit application
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    // Camera controller
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        g_Camera.ProcessKeyboard(CameraMovement::FORWARD, g_Time.DeltaTime());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        g_Camera.ProcessKeyboard(CameraMovement::BACKWARD, g_Time.DeltaTime());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        g_Camera.ProcessKeyboard(CameraMovement::LEFT, g_Time.DeltaTime());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        g_Camera.ProcessKeyboard(CameraMovement::RIGHT, g_Time.DeltaTime());
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        g_Camera.MovementSpeed(SPEED * 50.0f);
    } else {
        g_Camera.MovementSpeed(SPEED * 2.5f);
    }
    
    // Time controller
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        g_Time.TimeMultiplayer(0.0f);
    } else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        g_Time.TimeMultiplayer(1.0f);
    } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        g_Time.TimeMultiplayer(2.0f);
    } else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        g_Time.TimeMultiplayer(5.0f);
    } else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        g_Time.TimeMultiplayer(15.0f);
    }
    
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        g_Camera.Position(glm::vec3(-5.0f, 20.0f, 5.0f));
        g_Camera.Yaw(-30.0f);
        g_Camera.Pitch(-30.0f);
    }
}

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos) {
    static float last_x = SCR_WIDTH / 2.0f;
    static float last_y = SCR_HEIGHT / 2.0f;
    static bool firstMouse = true;
    
    if (firstMouse) {
        last_x = x_pos;
        last_y = y_pos;
        firstMouse = false;
    }
    
    float xoffset = x_pos - last_x;
    float yoffset = last_y - y_pos; // Reversed since y-coordinates go from bottom to top
    
    last_x = x_pos;
    last_y = y_pos;
    
    g_Camera.ProcessMouseMovement(xoffset, yoffset, GL_TRUE);
}
