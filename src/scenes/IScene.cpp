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

void IScene::RegisterDrawable(IDrawable* component) {
    m_DrawManager.RegsiterDrawCall(component);
}

void IScene::UnregisterDrawable(IDrawable* component) {
    m_DrawManager.UnregisterDrawCall(component);
}

void IScene::RegisterLightSource(ILightSource *light_source) {
    m_DrawManager.RegisterLightSource(light_source);
}

void IScene::UnregisterLightSource(ILightSource *light_source) {
    m_DrawManager.UnregisterLightSource(light_source);
}

std::shared_ptr<Object> IScene::CreateObject(std::string name) {
    return m_ObjectManager.CreateObject(*this, name);
}
