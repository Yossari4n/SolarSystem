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
public:
    Object(std::string name = "object");
    ~Object();
    
    void Initialize();
    void Update();
    void Destroy();
    
    void AddComponent(IComponent *component);
    void RemoveComponent(IComponent *component);
    
    void RegisterUpdateCall(IComponent *component);
    void UnregisterUpdateCall(IComponent *component);
    
    const std::string& Name() const { return m_Name; }
    void Name(const std::string& name) { m_Name = name; }
    
    const glm::mat4& Model() const { return m_Model; }
    
    const glm::vec3& Position() const { return m_Position; }
    void Position(const glm::vec3& position);
    
    const glm::vec3& Rotation() const { return m_Rotation; }
    void Rotation(const glm::vec3& rotation);
    
    const glm::vec3& Scale() const { return m_Scale; }
    void Scale(const glm::vec3& scale);
    
private:
    std::string m_Name;
    
    std::vector<IComponent*> m_Components;
    std::vector<IComponent*> m_UpdateCalls;
    
    glm::mat4 m_Model;
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
    
    void UpdateModel();
};

#endif
