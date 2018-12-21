#include "DrawManager.h"

DrawManager::DrawManager() {
    
}

DrawManager::~DrawManager() {
    delete [] m_ShaderPrograms;
}

void DrawManager::Initialize() {
    m_ShaderPrograms = new ShaderProgram[IDrawable::ShaderType::COUNT];
    
    m_ShaderPrograms[IDrawable::ShaderType::LIGHT_SOURCE].AttachShaders("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/LightSource.vs",
                                                                        "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/LightSource.fs");
    
    m_ShaderPrograms[IDrawable::ShaderType::LIGHT_RECEIVER].AttachShaders("/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/LightReceiver.vs",
                                                                          "/Users/jakubstokowski/Desktop/OpenGL/SolarSystem/src/shaders/LightReceiver.fs");
}

void DrawManager::RegsiterDrawCall(IDrawable *draw) {
    if (std::find(m_Drawables.begin(), m_Drawables.end(), draw) == m_Drawables.end()) {
        m_Drawables.push_back(draw);
    }
}

void DrawManager::UnregisterDrawCall(IDrawable *draw) {
    auto it = std::find(m_Drawables.begin(), m_Drawables.end(), draw);
    
    if (it != m_Drawables.end()) {
        long index = std::distance(m_Drawables.begin(), it);
        m_Drawables.erase(m_Drawables.begin() + index);
    }
}

void DrawManager::CallDraws() const {
    for (auto it = m_Drawables.begin(); it != m_Drawables.end(); it++) {
        int shader_type = (*it)->m_ShaderType;
        ShaderProgram& curr_shader = m_ShaderPrograms[shader_type];
        curr_shader.Use();
        
        // pv = projection * view
        glm::mat4 pv = g_Camera.Projection() * g_Camera.ViewMatrix();
        curr_shader.SetMat4("pv", pv);
        
        if (shader_type == IDrawable::ShaderType::LIGHT_RECEIVER) {
            curr_shader.SetVec3("viewPos", g_Camera.Position());
            
            curr_shader.SetFloat("material.shininess", 32.0f);
            
            curr_shader.SetVec3("pointLights[0].position", glm::vec3(0.0f, 0.0f, 0.0f));
            curr_shader.SetVec3("pointLights[0].ambient", 0.1f, 0.1f, 0.1f);
            curr_shader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
            curr_shader.SetFloat("pointLights[0].constant", 1.0f);
            curr_shader.SetFloat("pointLights[0].linear", 0.0014f);
            curr_shader.SetFloat("pointLights[0].quadratic", 0.000007f);
        }
        
        (*it)->Draw(curr_shader);
    }
}

void DrawManager::SetLightProperties(const ShaderProgram &shader) {
    
}
