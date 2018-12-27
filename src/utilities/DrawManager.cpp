#include "DrawManager.h"

DrawManager::DrawManager() {
}

DrawManager::~DrawManager() {
}

void DrawManager::Initialize() {
    m_ShaderPrograms[IDrawable::ShaderTypes::LIGHT_SOURCE].AttachShaders("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/LightSource.vs",
                                                                        "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/LightSource.fs");
    
    m_ShaderPrograms[IDrawable::ShaderTypes::LIGHT_RECEIVER].AttachShaders("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/LightReceiver.vs",
                                                                          "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/LightReceiver.fs");
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

void DrawManager::RegisterLightSource(IDrawable* light_source) {
    // implement
}

void DrawManager::UnregisterLightSource(IDrawable* light_source) {
    // implement
}

void DrawManager::CallDraws() const {
    for (auto it = m_Drawables.begin(); it != m_Drawables.end(); it++) {
        int shader_type = (*it)->ShaderType();
        const ShaderProgram& curr_shader = m_ShaderPrograms[shader_type];
        curr_shader.Use();
        
        // pv = projection * view
        glm::mat4 pv = g_Camera.Projection() * g_Camera.ViewMatrix();
        curr_shader.SetMat4("pv", pv);
        
        if (shader_type == IDrawable::ShaderTypes::LIGHT_RECEIVER) {
            curr_shader.SetVec3("viewPos", g_Camera.Position());
            curr_shader.SetFloat("material.shininess", 32.0f);
            
            // for all ILightSources SetLightProperties
            
            // deprecated
            curr_shader.SetVec3("pointLights[0].position", glm::vec3(0.0f, 0.0f, 0.0f));
            curr_shader.SetVec3("pointLights[0].ambient", glm::vec3(0.1f));
            curr_shader.SetVec3("pointLights[0].diffuse", glm::vec3(0.8f));
            curr_shader.SetVec3("pointLights[0].specular", glm::vec3(0.5f));
            curr_shader.SetFloat("pointLights[0].constant", 1.0f);
            curr_shader.SetFloat("pointLights[0].linear", 0.0014f);
            curr_shader.SetFloat("pointLights[0].quadratic", 0.000007f);
        }
        
        (*it)->Draw(curr_shader);
    }
}
