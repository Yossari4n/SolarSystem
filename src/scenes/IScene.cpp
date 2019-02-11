#include "IScene.h"

#include "../rendering/IDrawable.h"
#include "../rendering/ILightSource.h"
#include "../utilities/Time.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"

IScene::IScene() {
    m_Running = true;
    m_FrameRateLimit = 0.0f;
}

void IScene::PreRun() {
    m_Running = true;
    
    m_DrawManager.Initialize();
    m_ObjectManager.InitializeObjects();
}

void IScene::Run() {
    g_Time.Initialize();
    
    while (m_Running && !glfwWindowShouldClose(g_Window())) {
        do {
            g_Time.Hold();
        } while (g_Time.DeltaTime() < m_FrameRateLimit);
        
        g_Time.Update();
        g_Input.Update(g_Window());
        
        m_ObjectManager.UpdateObjects();
        m_DrawManager.CallDraws();
    
        glfwPollEvents();
    }
}

void IScene::PostRun() {
    m_ObjectManager.DestroyObjects();
}

void IScene::Exit() {
    m_Running = false;
}

Object* IScene::CreateObject(std::string name) {
    return m_ObjectManager.CreateObject(*this, name);
}

float IScene::FrameRateLimit() const {
    return 1.0f / m_FrameRateLimit;
}

void IScene::FrameRateLimit(unsigned int frame_rate) {
    m_FrameRateLimit = frame_rate != 0 ? 1.0f / (float)frame_rate : 0.0f;
}
