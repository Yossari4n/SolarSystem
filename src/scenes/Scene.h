#ifndef Scene_hpp
#define Scene_hpp

#include <iostream>

#include "../utilities/Time.h"
#include "../utilities/ObjectManager.h"
#include "../utilities/DrawManager.h"

class Scene {
public:
    void Initialize();
    void Run();
    void PostRun();
    
//private:
    ObjectManager m_ObjectManager;
    DrawManager m_DrawManager;
    
protected:
    // Object* CreateObject();
    // 
};

#endif
