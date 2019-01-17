#include "Object.h"

#include "IComponent.h"


Object::Object(class IScene& scene, std::string name)
    : m_Name(name)
    , m_Scene(scene)
    , m_Position(glm::vec3(0.0f))
    , m_Rotation(glm::vec3(0.0f))
    , m_Scale(glm::vec3(1.0f)){
    UpdateModel();
}

Object::~Object() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        (*it)->m_Object = nullptr;
    }
}

void Object::Initialize() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        (*it)->Initialize();
    }
}

void Object::Update() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        (*it)->Update();
    }
}

void Object::Destroy() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        (*it)->Destroy();
    }
}

const glm::mat4& Object::Model() {
    return m_Model;
}

void Object::Position(const glm::vec3& position) {
    m_Position = position;
    
    UpdateModel();
}

void Object::Move(const glm::vec3& vector) {
    m_Position = m_Position + vector;
    
    UpdateModel();
}

void Object::Rotation(const glm::quat &rotation) {
    m_Rotation = rotation;
    
    UpdateModel();
}

void Object::Rotate(const glm::quat &rotation) {
    m_Rotation =  m_Rotation * rotation;
    
    UpdateModel();
}

void Object::Scale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

void Object::UpdateModel() {
    glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), m_Position);
    glm::mat4 rotation_matrix = glm::toMat4(m_Rotation);
    glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), m_Scale);
    
    m_Model = translate_matrix * rotation_matrix * scale_matrix;
}
