#ifndef Object_h
#define Object_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <algorithm>

class IComponent;
class Scene;

class Object {
    typedef void (IComponent::*UpdateCall)(void);
    
public:
    Object(std::string name = "object");
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
    void RemoveComponent() {}
    
    template <class T>
    std::shared_ptr<T> GetComponent() {}
    
    const std::string& Name() const { return m_Name; }
    void Name(const std::string& name) { m_Name = name; }
    
    const glm::mat4& Model() const { return m_Model; }
    
    const glm::vec3& Position() const { return m_Position; }
    void Position(const glm::vec3& position);
    void Move(const glm::vec3& vector);
    
    const glm::vec3& Rotation() const { return m_Rotation; }
    void Rotation(const glm::vec3& rotation);
    void Rotate(const glm::vec3& rotation);
    
    const glm::vec3& Scale() const { return m_Scale; }
    void Scale(const glm::vec3& scale);
    
private:
    std::string m_Name;
    
    std::vector<std::shared_ptr<IComponent>> m_Components;
    
    glm::mat4 m_Model;
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
    
    void UpdateModel();
};

#endif
