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

#define EARTH_RADIUS (1.21f / M_PI)
#define EARTH_ROTATION_SPEED
#define EARTH_ORBIT_RADIUS (150.0f / 3.0f)
#define EARTH_ORBIT_ANGULAR_VELOCITY (DOUBLE_PI / 60.0f) // w = 2pi / T, where T := time for one cycle

// Screen setting
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Controller
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_input(GLFWwindow *window);

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, -30.0f));
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
    
    Sphere::Init();
    
    AstronomicalObject sun("Sun", 0.0f);
    sun.Color(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    sun.Scale(glm::vec3(109.0f / DOUBLE_PI));
    
    AstronomicalObject merkury("Merkur", 0.0f);
    merkury.Scale(glm::vec3(0.38f * EARTH_RADIUS));
    merkury.Color(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    merkury.Orbit(Orbit(&sun.Position(), EARTH_ORBIT_RADIUS * 0.38f, EARTH_ORBIT_ANGULAR_VELOCITY * 1.0 / 0.24f));
    
    AstronomicalObject wenus("Wenus", 0.0f);
    wenus.Scale(glm::vec3(0.9f * EARTH_RADIUS));
    wenus.Color(glm::vec4(1.0f));
    wenus.Orbit(Orbit(&sun.Position(), EARTH_ORBIT_RADIUS * 0.72f, EARTH_ORBIT_ANGULAR_VELOCITY * 1.0f / 0.61f));
    
    AstronomicalObject earth("Earth", 0.0f);
    earth.Scale(glm::vec3(EARTH_RADIUS));
    earth.Color(glm::vec4(1.0f));
    earth.Orbit(Orbit(&sun.Position(), EARTH_ORBIT_RADIUS, EARTH_ORBIT_ANGULAR_VELOCITY));
    
    AstronomicalObject mars("Mars", 0.0f);
    mars.Scale(glm::vec3(0.53f * EARTH_RADIUS));
    mars.Color(glm::vec4(1.0f));
    mars.Orbit(Orbit(&sun.Position(), EARTH_ORBIT_RADIUS * 1.52, EARTH_ORBIT_ANGULAR_VELOCITY * 1.0f / 1.88f));
    
    AstronomicalObject jupiter("Jupiter", 0.0f);
    jupiter.Scale(glm::vec3(11.2f * EARTH_RADIUS));
    jupiter.Color(glm::vec4(1.0f));
    jupiter.Orbit(Orbit(&sun.Position(), EARTH_ORBIT_RADIUS * 5.2f, EARTH_ORBIT_ANGULAR_VELOCITY * 1.0f / 11.86f));
    
    AstronomicalObject saturn("Saturn", 0.0f);
    saturn.Scale(glm::vec3(9.4f * EARTH_RADIUS));
    saturn.Color(glm::vec4(1.0f));
    saturn.Orbit(Orbit(&sun.Position(), EARTH_ORBIT_RADIUS * 9.53f, EARTH_ORBIT_ANGULAR_VELOCITY * 1.0f / 29.44f));
    
    AstronomicalObject uranus("Uranus", 0.0f);
    uranus.Scale(glm::vec3(4.0f * EARTH_RADIUS));
    uranus.Color(glm::vec4(1.0f));
    uranus.Orbit(Orbit(&sun.Position(), EARTH_ORBIT_RADIUS * 19.19f, EARTH_ORBIT_ANGULAR_VELOCITY * 1.0f / 84.07f));
    
    AstronomicalObject neptune("Neptune", 0.0f);
    neptune.Scale(glm::vec3(3.8f * EARTH_RADIUS));
    neptune.Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    neptune.Orbit(Orbit(&sun.Position(), EARTH_ORBIT_RADIUS * 30.06f, EARTH_ORBIT_ANGULAR_VELOCITY * 1.0f / 164.88f));
    
    std::array<AstronomicalObject, 8> planets({merkury, wenus, earth, mars, jupiter, saturn, uranus, neptune});
    
    // Settings
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PRIMITIVE_RESTART_INDEX);
    
    shader_light_source.Use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5000.0f);
    shader_light_source.SetMat4("projection", projection);
    
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
        sun.Update();
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
    
    // End of application
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
    float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset, GL_TRUE);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
