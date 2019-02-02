#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#ifndef Transform_h
#define Transform_h

class Transform {
public:
    enum Space {
        LOCAL = 0,
        WORLD
    };
    
    Transform();
    
    const glm::mat4& Model();
    
    const glm::vec3& Position() const { return m_Position; }
    void Position(const glm::vec3& position);
    void Move(const glm::vec3& vector);
    
    const glm::quat& Rotation() const { return m_Rotation; }
    void Rotation(const glm::quat& rotation);
    void Rotate(const glm::quat& rotation, Transform::Space space = Transform::Space::LOCAL);
    
    const glm::vec3& Scale() const { return m_Scale; }
    void Scale(const glm::vec3& scale);
    
private:
    glm::mat4 m_Model;
    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;
    
    void UpdateModel();
};

#endif
