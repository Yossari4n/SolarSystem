#include "DrawManager.h"

#include "IDrawable.h"
#include "ILightSource.h"
#include "../utilities/Window.h"
#include "../utilities/Cubemap.h"
#include "../cbs/components/Camera.h"

DrawManager::DrawManager()
    : line(glm::vec3(-2.0f, 0.0f, 78.0f), glm::vec3(4.0f, 0.0f, 78.0f), glm::vec3(1.0f), 100.0f)
    , m_Skybox(nullptr)
    , m_Background(0.0f, 0.0f, 0.0f) {
    
}

DrawManager::~DrawManager() {
    if (m_Skybox != nullptr) {
        delete m_Skybox;
    }
}

void DrawManager::Initialize() {
    m_ShaderPrograms[ShaderProgram::TYPE::COLOR_PURE].AttachShaders("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/COLOR_PURE.vs",
                                                                    "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/COLOR_PURE.fs");
    
    m_ShaderPrograms[ShaderProgram::TYPE::TEXTURE_PURE].AttachShaders("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/TEXTURE_PURE.vs",
                                                                      "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/TEXTURE_PURE.fs");
    
    m_ShaderPrograms[ShaderProgram::TYPE::TEXTURE_LIGHT_RECEIVER].AttachShaders("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/TEXTURE_LIGHT_RECEIVER.vs",
                                                                                "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/TEXTURE_LIGHT_RECEIVER.fs");

    m_ShaderPrograms[ShaderProgram::TYPE::SKYBOX].AttachShaders("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/SKYBOX.vs",
                                                                "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/SKYBOX.fs");
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void DrawManager::RegisterCamera(Camera *camera) {
    m_Camera = camera;
}

void DrawManager::Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front) {
    if (m_Skybox != nullptr) {
        delete m_Skybox;
    }
    
    m_Skybox = new Cubemap(right, left, top, bottom, back, front, ShaderProgram::TYPE::SKYBOX);
}

void DrawManager::Background(const glm::vec3& background) {
    m_Background = background;
}

void DrawManager::RegsiterDrawCall(IDrawable* component) {
    if (std::find(m_Drawables.begin(), m_Drawables.end(), component) == m_Drawables.end()) {
        m_Drawables.push_back(component);
    }
}

void DrawManager::UnregisterDrawCall(IDrawable* component) {
    auto it = std::find(m_Drawables.begin(), m_Drawables.end(), component);
    
    if (it != m_Drawables.end()) {
        long index = std::distance(m_Drawables.begin(), it);
        m_Drawables.erase(m_Drawables.begin() + index);
    }
}

void DrawManager::RegisterLightSource(ILightSource* light_source) {
    if (std::find(m_LightSources.begin(), m_LightSources.end(), light_source) == m_LightSources.end()) {
        m_LightSources.push_back(light_source);
    }
}

void DrawManager::UnregisterLightSource(ILightSource* light_source) {
    auto it = std::find(m_LightSources.begin(), m_LightSources.end(), light_source);
    
    if (it != m_LightSources.end()) {
        long index = std::distance(m_LightSources.begin(), it);
        m_LightSources.erase(m_LightSources.begin() + index);
    }
}

void DrawManager::CallDraws() const {
    glClearColor(m_Background.x, m_Background.y, m_Background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 pv = m_Camera->Projection() * m_Camera->ViewMatrix();
    
    // Draw objects
    for (auto it = m_Drawables.begin(); it != m_Drawables.end(); it++) {
        int shader_type = (*it)->ShaderType();
        const ShaderProgram& curr_shader = m_ShaderPrograms[shader_type];
        
        curr_shader.Use();
        curr_shader.SetMat4("pv", pv);
        
        if (shader_type == ShaderProgram::TYPE::TEXTURE_LIGHT_RECEIVER) {
            curr_shader.SetVec3("viewPos", m_Camera->Position());
            curr_shader.SetFloat("material.shininess", 32.0f);
            
            // for all ILightSources SetLightProperties
            for (auto it = m_LightSources.begin(); it != m_LightSources.end(); ++it) {
                (*it)->SetLightProperties(curr_shader);
            }
        }
        
        (*it)->Draw(curr_shader);
    }
    
    // Draw skybox
    if (m_Skybox != nullptr) {
        glDepthFunc(GL_LEQUAL);
        
        m_ShaderPrograms[ShaderProgram::TYPE::SKYBOX].Use();
        m_ShaderPrograms[ShaderProgram::TYPE::SKYBOX].SetMat4("view", glm::mat4(glm::mat3(m_Camera->ViewMatrix())));
        m_ShaderPrograms[ShaderProgram::TYPE::SKYBOX].SetMat4("projection", m_Camera->Projection());
        
        m_Skybox->Draw(m_ShaderPrograms[ShaderProgram::TYPE::SKYBOX]);
        
        glDepthFunc(GL_LESS);
    }
    
    glfwSwapBuffers(g_Window());
}
