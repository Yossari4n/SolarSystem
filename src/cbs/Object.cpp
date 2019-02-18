#include "Object.h"

#include "components/AstronomicalObject.h"

Object::Object(class IScene& scene, std::string name)
    : m_Name(name)
    , m_Scene(scene){
}

Object::~Object() {
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        (*it)->m_Object = nullptr;
    }
}

void Object::Initialize() {
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        (*it)->Initialize();
    }
}

void Object::Update() {
    // To prevent premature destruction of components deleted in update
    // this loop can't use iterators and for each component must increment shared pointer counter
    for (auto&& ptr_comp : m_Components) {
        std::shared_ptr<IComponent>(ptr_comp)->Update();
    }
}

void Object::Destroy() {
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        (*it)->Destroy();
    }
}
