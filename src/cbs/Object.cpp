#include "Object.h"

#include "IComponent.h"


Object::Object(class IScene& scene, std::string name)
    : m_Name(name)
    , m_Scene(scene){
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
