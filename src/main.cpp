#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Camera.h"
#include "Time.h"
#include "Sphere.h"
#include "AstronomicalObject.h"

#define DOUBLE_PI (M_PI * 2)

// Screen setting
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Controller
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_input(GLFWwindow *window);

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, -50.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Global time struct
Time g_Time;

int main() {
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
    glfwSetScrollCallback(window, scroll_callback);
    
    // Capture the mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }
     
    // Shader programs
    ShaderProgram shader_light_source;
    shader_light_source.AttachShaders("/Users/jakubstokowski/Desktop/openGL/SolarSystem/src/VertexShader.vs",
                                      "/Users/jakubstokowski/Desktop/openGL/SolarSystem/src/FramgentShader.fs");
    
    // Settings
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PRIMITIVE_RESTART_INDEX);
    
    shader_light_source.Use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5000.0f);
    shader_light_source.SetMat4("projection", projection);
    
    Sphere::Init();
    
    // real size: 1 392 000
    Sphere sun;
    sun.Color(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    sun.Scale(glm::vec3(109.0f / DOUBLE_PI));
    
    // real size: 4 879, real orbit radius: 57 909 170
    AstronomicalObject merkury("Merkur", &sun.Position(), 57.0f / 3.0f, 0.0f);
    merkury.Color(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    merkury.Scale(glm::vec3(0.48f / DOUBLE_PI));
    
    // real size: 12 104, real orbit radius: 108 208 926
    AstronomicalObject wenus("Wenus", &sun.Position(), 108.0f / 3.0f, 0.0f);
    wenus.Color(glm::vec4(1.0f));
    wenus.Scale(glm::vec3(0.9f / DOUBLE_PI));
    
    // real size: 12 756, real orbit radius: 149 597 887
    AstronomicalObject ziemia("Ziemia", &sun.Position(), 140.0f / 3.0f, 0.0f);
    ziemia.Color(glm::vec4(1.0f));
    ziemia.Scale(glm::vec3(1.0f / DOUBLE_PI));
    
    // real size: 6 805, real orbit radius: 227 936 637
    AstronomicalObject mars("Mars", &sun.Position(), 227.0f / 3.0f, 0.0f);
    mars.Color(glm::vec4(1.0f));
    mars.Scale(glm::vec3(0.53f / DOUBLE_PI));
    
    // real size: 142 984, real orbit radius: 778 412 027
    AstronomicalObject jowisz("Jowisz", &sun.Position(), 778.0f / 3.0f, 0.0f);
    jowisz.Color(glm::vec4(1.0f));
    jowisz.Scale(glm::vec3(11.2f / DOUBLE_PI));
    
    // real size: 120 536, real orbit radius: 1 426 725 413
    AstronomicalObject saturn("Saturn", &sun.Position(), 1426.0f / 3.0f, 0.0f);
    saturn.Color(glm::vec4(1.0f));
    saturn.Scale(glm::vec3(9.4f / DOUBLE_PI));
    
    // real size: 51 118, real orbit radius: 2 870 972 220
    AstronomicalObject uran("Uran", &sun.Position(), 2870.0f / 3.0f, 0.0f);
    uran.Color(glm::vec4(1.0f));
    uran.Scale(glm::vec3(4.0f / DOUBLE_PI));
    
    // real size: 49 528, real orbit radius: 4 498 252 900
    AstronomicalObject neptun("Neptun", &sun.Position(), 4498.0f / 3.0f, 0.0f);
    neptun.Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    neptun.Scale(glm::vec3(3.8f / DOUBLE_PI));
    
    std::array<AstronomicalObject, 9> planets({merkury, wenus, ziemia, mars, jowisz, saturn, uran, neptun});
    
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Per-frame time logic
        g_Time.current_time = glfwGetTime();
        g_Time.delta_time = g_Time.current_time - g_Time.last_frame;
        g_Time.last_frame = g_Time.current_time;
        
        // Clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Input
        process_input(window);
        
        // Update
        for (AstronomicalObject& planet : planets) {
            planet.Update();
        }
        
        // Render objects
        sun.Draw(shader_light_source);
        for (const AstronomicalObject& planet : planets) {
            planet.Draw(shader_light_source);
        }
        
        // Get camera view
        glm::mat4 view = camera.ViewMatrix();
        shader_light_source.SetMat4("view", view);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    // Camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::FORWARD, g_Time.delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::BACKWARD, g_Time.delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::LEFT, g_Time.delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::RIGHT, g_Time.delta_time);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.MovementSpeed(SPEED * 50.0f);
    } else {
        camera.MovementSpeed(SPEED * 5.0f);
    }
    
    
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset, GL_TRUE);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
