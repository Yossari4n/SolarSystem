#ifndef ObjectManager_h
#define ObjectManager_h

#include <vector>
#include <string>

class IScene;
class Object;

class ObjectManager {
public:
    ~ObjectManager();
    
    void InitializeObjects();
    void UpdateObjects();
    void DestroyObjects();
    
    Object* CreateObject(IScene& scene, std::string name = "");
    Object* CreateObject(const Object* other, std::string name = "");
    
private:
    std::vector<Object*> m_Objects;
};

#endif
