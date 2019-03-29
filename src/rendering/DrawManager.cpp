#include "DrawManager.h"

#include "IDrawable.h"
#include "ILightSource.h"
#include "../utilities/Window.h"
#include "../utilities/Cubemap.h"
#include "../cbs/components/Camera.h"

DrawManager::DrawManager()
    : m_Skybox(nullptr)
    , m_Background(0.0f, 0.0f, 0.0f) {
}

DrawManager::~DrawManager() {
    
}

void DrawManager::Initialize() {
    m_ShaderPrograms[ShaderProgram::Type::PURE_COLOR].AttachShaders("src/shaders/PURE_COLOR.vs",
                                                                    "src/shaders/PURE_COLOR.fs");
    
    m_ShaderPrograms[ShaderProgram::Type::PURE_TEXTURE].AttachShaders("src/shaders/PURE_TEXTURE.vs",
                                                                      "src/shaders/PURE_TEXTURE.fs");
    
    m_ShaderPrograms[ShaderProgram::Type::PHONG_TEXTURE].AttachShaders("src/shaders/PHONG_TEXTURE.vs",
                                                                       "src/shaders/PHONG_TEXTURE.fs");
    m_ShaderPrograms[ShaderProgram::Type::PHONG_TEXTURE].Traits(ShaderProgram::Trait::LIGHT_RECEIVER);

    m_ShaderPrograms[ShaderProgram::Type::SKYBOX].AttachShaders("src/shaders/SKYBOX.vs",
                                                                "src/shaders/SKYBOX.fs");
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void DrawManager::RegisterCamera(Camera *camera) {
    m_Camera = camera;
}

Camera* DrawManager::MainCamera() const {
    return m_Camera;
}

void DrawManager::Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front) {
    m_Skybox = std::make_unique<Cubemap>(right, left, top, bottom, back, front, ShaderProgram::Type::SKYBOX);
}

void DrawManager::Background(const glm::vec3& background) {
    m_Background = background;
}

void DrawManager::RegisterDrawCall(IDrawable* component) {
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
    for (auto it = m_Drawables.cbegin(); it != m_Drawables.cend(); it++) {
        int shader_type = (*it)->ShaderType();
        const ShaderProgram& curr_shader = m_ShaderPrograms[shader_type];
        
        curr_shader.Use();
        curr_shader.SetMat4("pv", pv);
        
        // Set light properties
        if (curr_shader.Traits() & ShaderProgram::Trait::LIGHT_RECEIVER) {
            curr_shader.SetVec3("view_pos", m_Camera->Object().Transform().Position());
            curr_shader.SetFloat("material.shininess", 32.0f);
            
            for (auto it = m_LightSources.begin(); it != m_LightSources.end(); ++it) {
                (*it)->SetLightProperties(curr_shader);
            }
        }
        
        (*it)->Draw(curr_shader);
    }
    
    // Draw skybox
    if (m_Skybox != nullptr) {
        glDepthFunc(GL_LEQUAL);
        
        m_ShaderPrograms[ShaderProgram::Type::SKYBOX].Use();
        m_ShaderPrograms[ShaderProgram::Type::SKYBOX].SetMat4("pv", m_Camera->Projection() * glm::mat4(glm::mat3(m_Camera->ViewMatrix())));
        
        m_Skybox->Draw(m_ShaderPrograms[ShaderProgram::Type::SKYBOX]);
        
        glDepthFunc(GL_LESS);
    }
    
    glfwSwapBuffers(g_Window);
}
