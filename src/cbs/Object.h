#ifndef Object_h
#define Object_h

#include "Transform.h"
#include "components/IComponent.h"
#include "../scenes/IScene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <string>
#include <vector>
#include <algorithm>

class Object {
public:
    Object(IScene& scene, std::string name = "object");
    ~Object();
    
    void Initialize();
    void Update();
    void Destroy();
    
    template <class T, typename ...Args>
    T* CreateComponent(Args&&... params) {
        // Create new IComponent
        auto comp = std::make_shared<T>(params...);
        comp->m_Object = this;
        
        // Register IComponent in a pool
        m_Components.push_back(comp);

        // Return pointer of T type
        return comp.get();
    }
    
    template <class T>
    T* CreateComponent(T* other) {
        // Create new IComponent by invoking copy constructor
        auto comp = std::make_shared<T>(*other);
        comp->m_Object = this;
        
        // Register IComponent in a pool
        m_Components.push_back(comp);
        
        // Return pointer of T type
        return comp.get();
    }
    
    template <class T>
    void RemoveComponent() {
        m_Components.erase(std::remove_if(m_Components.begin(),
                                          m_Components.end(),
                                          [](std::shared_ptr<IComponent> &comp) {
                                              if (dynamic_cast<T*>(comp.get()) != nullptr) {
                                                  comp->Destroy();
                                                  return true;
                                              }
                                              
                                              return false;
                                          }),
                           m_Components.end());
    }
    
    template <class T>
    T* GetComponent() {
        auto it = m_Components.begin();
        
        while (it != m_Components.end() && dynamic_cast<T*>((*it).get()) == nullptr ) {
            it++;
        }
        
        return dynamic_cast<T*>((*it).get());
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
