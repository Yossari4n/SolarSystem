#include "IScene.h"

#include "../rendering/IDrawable.h"
#include "../rendering/ILightSource.h"
#include "../utilities/Time.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"

void IScene::PreRun() {
    m_Running = true;
    
    m_DrawManager.Initialize();
    m_ObjectManager.InitializeObjects();
}

void IScene::Run() {
    g_Time.Initialize();
    
    while (m_Running && !glfwWindowShouldClose(g_Window())) {
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

std::shared_ptr<Object> IScene::CreateObject(std::string name) {
    return m_ObjectManager.CreateObject(*this, name);
}
