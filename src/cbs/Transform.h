#ifndef Transform_h
#define Transform_h

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform {
public:
    enum SPACE {
        LOCAL,
        WORLD
    };
    
    Transform();
    
    const glm::mat4& Model();
    
    const glm::vec3& Position() const { return m_Position; }
    void Position(const glm::vec3& position);
    void Move(const glm::vec3& vector, Transform::SPACE space);
    
    const glm::quat& Rotation() const { return m_Rotation; }
    void Rotation(const glm::quat& rotation);
    void Rotate(const glm::quat& rotation, Transform::SPACE space = Transform::SPACE::LOCAL);
    
    const glm::vec3& Scale() const { return m_Scale; }
    void Scale(const glm::vec3& scale);
    
    glm::vec3 Front() { return m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f); }
    glm::vec3 Up() { return m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f); }
    glm::vec3 Right() { return m_Rotation * glm::vec3(0.0f, 0.0f, 1.0f); }
    
private:
    glm::mat4 m_Model;
    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;
    
    void UpdateModel();
};

#endif
