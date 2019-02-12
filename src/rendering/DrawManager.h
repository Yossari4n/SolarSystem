#ifndef DrawManager_h
#define DrawManager_h

#include "ShaderProgram.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <array>

class Camera;
class IDrawable;
class ILightSource;
class Cubemap;

class DrawManager {
public:
    DrawManager();
    ~DrawManager();
    
    void Initialize();
    
    void RegisterCamera(Camera* camera);
    
    void Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
    void Background(const glm::vec3& background);
    
    void RegsiterDrawCall(IDrawable* component);
    void UnregisterDrawCall(IDrawable* component);
    
    void RegisterLightSource(ILightSource* light_source);
    void UnregisterLightSource(ILightSource* light_source);
    
    void CallDraws() const;
    
private:
    Camera* m_Camera;
    
    glm::vec3 m_Background;
    std::unique_ptr<Cubemap> m_Skybox;
    
    std::vector<IDrawable*> m_Drawables;
    std::vector<IDrawable*> m_PostProcessing;
    
    std::vector<ILightSource*> m_LightSources;
    
    std::array<ShaderProgram, ShaderProgram::TYPE::COUNT> m_ShaderPrograms;
};

#endif
