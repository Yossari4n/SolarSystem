#include "IScene.h"

#include "../rendering/IDrawable.h"
#include "../rendering/ILightSource.h"

void IScene::PreRun() {
    m_DrawManager.Initialize();
    
    m_ObjectManager.InitializeObjects();
}

void IScene::Run() {
    m_ObjectManager.UpdateObjects();
    m_DrawManager.CallDraws();
}

void IScene::PostRun() {
    m_ObjectManager.DestroyObjects();
}

std::shared_ptr<Object> IScene::CreateObject(std::string name) {
    return m_ObjectManager.CreateObject(*this, name);
}
