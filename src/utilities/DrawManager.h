#ifndef DrawManager_h
#define DrawManager_h

#include <vector>
#include <array>

#include "../components/Camera.h"
#include "../rendering/IDrawable.h"
#include "../rendering/ILighSource.h"
#include "../rendering/ShaderProgram.h"

class DrawManager {
public:
    DrawManager();
    ~DrawManager();
    
    void Initialize();
    
    void RegsiterDrawCall(IDrawable* component);
    void UnregisterDrawCall(IDrawable* component);
    
    void RegisterLightSource(IDrawable* light_source);
    void UnregisterLightSource(IDrawable* light_source);
    
    void CallDraws() const;
    
private:
    std::vector<IDrawable*> m_Drawables;
    std::vector<IDrawable*> m_PostProcessing;
    
    std::vector<std::weak_ptr<ILighSource>> m_LightSources;
    
    std::array<ShaderProgram, IDrawable::ShaderTypes::COUNT> m_ShaderPrograms;
};

#endif
