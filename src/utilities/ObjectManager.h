#ifndef ObjectManager_h
#define ObjectManager_h

#include <vector>

#include "../components/Object.h"

class Object;

class ObjectManager {
public:
    void InitializeObjects();
    void UpdateObjects();
    void DestroyObjects();
    
    void RegisterObject(Object* object);
    void UnregisterObject(Object* object);
    
private:
    std::vector<Object*> m_Objects;
};

#endif
