#include "ObjectManager.h"

#include "../cbs/Object.h"
#include "../scenes/IScene.h"

void ObjectManager::InitializeObjects() {
    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++) {
        (*it)->Initialize();
    }
}

void ObjectManager::UpdateObjects() {
    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++) {
        (*it)->Update();
    }
}

void ObjectManager::DestroyObjects() {
    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++) {
        (*it)->Destroy();
    }
}

std::shared_ptr<Object> ObjectManager::CreateObject(IScene& scene, std::string name) {
    m_Objects.push_back(std::make_shared<Object>(scene, name));
    
    return m_Objects.at(m_Objects.size() - 1);
}
