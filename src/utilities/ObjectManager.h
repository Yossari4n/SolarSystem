#ifndef ObjectManager_h
#define ObjectManager_h

#include <vector>
#include <string>

class IScene;
class Object;

class ObjectManager {
public:
    void InitializeObjects();
    void UpdateObjects();
    void DestroyObjects();
    
    std::shared_ptr<Object> CreateObject(IScene& scene, std::string name = "");
private:
    std::vector<std::shared_ptr<Object>> m_Objects;
};

#endif
