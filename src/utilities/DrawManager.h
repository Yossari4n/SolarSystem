#ifndef DrawManager_h
#define DrawManager_h

#include <vector>

#include "../components/Camera.h"
#include "../rendering/IDrawable.h"
#include "../rendering/ShaderProgram.h"

class DrawManager {
public:
    DrawManager();
    ~DrawManager();
    
    void Initialize();
    
    void RegsiterDrawCall(IDrawable *draw);
    void UnregisterDrawCall(IDrawable *draw);
    
    void CallDraws() const;
    
private:
    std::vector<IDrawable*> m_Drawables; //TODO rename
    ShaderProgram *m_ShaderPrograms;
    
    void SetLightProperties(const ShaderProgram& shader);
};

#endif
