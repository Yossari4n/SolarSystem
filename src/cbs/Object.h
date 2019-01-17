#ifndef Object_h
#define Object_h

#include "../scenes/IScene.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <string>
#include <vector>
#include <algorithm>

class IComponent;

class Object {
public:
    Object(IScene& scene, std::string name = "object");
    ~Object();
    
    void Initialize();
    void Update();
    void Destroy();
    
    template <class T, typename ...Args>
    std::shared_ptr<T> CreateComponent(Args&&... params) {
        // Create new IComponent
        auto comp = std::make_shared<T>(std::forward<Args>(params)...);
        comp->m_Object = this;
        
        // Register IComponent in a pool
        m_Components.push_back(comp);

        // Return shared pointer of T type
        return std::dynamic_pointer_cast<T>(comp);
    }
    
    template <class T>
    void RemoveComponent() {
        m_Components.erase(std::remove_if(m_Components.begin(),
                                          m_Components.end(),
                                          [](std::shared_ptr<IComponent> &comp) { return dynamic_cast<T*>(comp.get()) != nullptr; }),
                           m_Components.end());
    }
    
    template <class T>
    std::shared_ptr<T> GetComponent() {
        auto it = m_Components.begin();
        
        while (it != m_Components.end() && dynamic_cast<T*>((*it).get()) == nullptr ) {
            it++;
        }
        
        return std::dynamic_pointer_cast<T>(*it);
    }
    
    const std::string& Name() const { return m_Name; }
    void Name(const std::string& name) { m_Name = name; }
    
    IScene& Scene() { return m_Scene; }
    Transform& Transform() { return m_Transform; }

private:
    std::string m_Name;
    
    class IScene& m_Scene;
    class Transform m_Transform;
    
    std::vector<std::shared_ptr<IComponent>> m_Components;
};

#endif
