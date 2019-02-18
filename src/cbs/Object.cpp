#include "Object.h"

#include "components/AstronomicalObject.h"

Object::Object(class IScene& scene, std::string name)
    : m_Name(name)
    , m_Scene(scene){
}

Object::Object(const Object& other, std::string name)
    : m_Name(name.empty() ? other.Name() + "_copy" : name)
    , m_Scene(other.m_Scene) {
    for (auto it = other.m_Components.begin(); it != other.m_Components.end(); ++it) {
        m_Components.push_back((*it)->Clone());
        m_Components[m_Components.size() - 1]->m_Object = this;
        m_Components[m_Components.size() - 1]->Initialize();
    }
}

Object::~Object() {
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        delete (*it);
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
    for (auto&& comp : m_Components) {
        comp->Update();
    }
}

void Object::Destroy() {
    for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
        (*it)->Destroy();
    }
}
