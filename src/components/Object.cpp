#include "Object.h"
#include "IComponent.h"
#include "../scenes/IScene.h"

Object::Object(class IScene& scene, std::string name)
    : m_Name(name)
    , m_Scene(scene)
    , m_Position(glm::vec3(0.0f))
    , m_Rotation(glm::vec3(0.0f))
    , m_Scale(glm::vec3(1.0f)) {
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

void Object::Position(const glm::vec3& position) {
    m_Position = position;
    
    UpdateModel();
}

void Object::Move(const glm::vec3 &vector) {
    m_Position = m_Position + vector;
    
    UpdateModel();
}

void Object::Rotation(const glm::vec3& rotation) {
    m_Rotation = rotation;
    
    UpdateModel();
}

void Object::Rotate(const glm::vec3 &rotation) {
    m_Rotation = m_Rotation + rotation;
    
    UpdateModel();
}

void Object::Scale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

void Object::UpdateModel() {
    m_Model = glm::translate(glm::mat4(), m_Position);
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_Model = glm::scale(m_Model, m_Scale);
}
