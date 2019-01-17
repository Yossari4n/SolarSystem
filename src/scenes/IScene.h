#ifndef Scene_hpp
#define Scene_hpp

#include "../cbs/ObjectManager.h"
#include "../rendering/DrawManager.h"

class IScene {
public:
    virtual void CreateScene() = 0;
    
    void PreRun();
    void Run();
    void PostRun();
    
    DrawManager& DrawManger() { return m_DrawManager; }
    
protected:
    std::shared_ptr<Object> CreateObject(std::string name = "");
    
private:
    ObjectManager m_ObjectManager;
    class DrawManager m_DrawManager;
};

#endif
