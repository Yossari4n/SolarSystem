#ifndef Scene_hpp
#define Scene_hpp

#include <iostream>

#include "../utilities/Time.h"
#include "../utilities/ObjectManager.h"
#include "../utilities/DrawManager.h"

class IScene {
public:
    virtual void CreateScene() = 0;
    
    void PreRun();
    void Run();
    void PostRun();
    
    void RegisterDrawable(IDrawable* component);
    void UnregisterDrawable(IDrawable* component);
    
protected:
    std::shared_ptr<Object> CreateObject(std::string name = "");
    
private:
    ObjectManager m_ObjectManager;
    DrawManager m_DrawManager;
};

#endif
