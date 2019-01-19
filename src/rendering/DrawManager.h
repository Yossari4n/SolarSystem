#ifndef DrawManager_h
#define DrawManager_h

#include "ShaderProgram.h"
#include "IDrawable.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <array>

class Camera;
class ILightSource;

class DrawManager {
public:
    DrawManager();
    ~DrawManager();
    
    void Initialize();
    
    void RegisterCamera(Camera* camera);
    
    void RegsiterDrawCall(IDrawable* component);
    void UnregisterDrawCall(IDrawable* component);
    
    void RegisterLightSource(ILightSource* light_source);
    void UnregisterLightSource(ILightSource* light_source);
    
    void CallDraws() const;
    
private:
    Camera* m_Camera;
    
    std::vector<IDrawable*> m_Drawables;
    std::vector<IDrawable*> m_PostProcessing;
    
    std::vector<ILightSource*> m_LightSources;
    
    std::array<ShaderProgram, ShaderProgram::TYPE::COUNT> m_ShaderPrograms;
};

#endif
