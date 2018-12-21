#include "ObjectManager.h"

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

void ObjectManager::RegisterObject(Object *object) {
    if (std::find(m_Objects.begin(), m_Objects.end(), object) == m_Objects.end()) {
        m_Objects.push_back(object);
    }
}

void ObjectManager::UnregisterObject(Object *object) {
    auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
    
    if (it != m_Objects.end()) {
        long index = std::distance(m_Objects.begin(), it);
        m_Objects.erase(m_Objects.begin() + index);
    }
}
