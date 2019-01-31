#include "Manager.h"

Manager::Manager(std::array<class Object *, 9> planets, std::array<float, 9> radiuses, FirstPersonController* fpc, ThirdPersonController* tpc)
    : m_Planets(planets)
    , m_Radiuses(radiuses)
    , m_FPC(fpc)
    , m_TPC(tpc) {
    
    m_Paused = false;
    m_TimeMultiplayersIndex = 0;
    m_TimeMultiplayers = { 1, 2, 4, 10, 50 };
}

void Manager::Initialize() {
    g_Time.TimeMultiplayer(m_TimeMultiplayers[0]);
    m_TPC->Deactivate();
}

void Manager::Update() {
    // Exit scene
    if (g_Input.GetKeyState(GLFW_KEY_ESCAPE) == Input::KeyState::PRESSED) {
        Object().Scene().Exit();
    }
    
    // Pause time
    if (g_Input.GetKeyState(GLFW_KEY_SPACE) == Input::KeyState::PRESSED) {
        if (m_Paused) {
            g_Time.TimeMultiplayer(m_TimeMultiplayers[m_TimeMultiplayersIndex]);
            m_Paused = false;
        } else {
            g_Time.TimeMultiplayer(0.0f);
            m_Paused = true;
        }
    }
    
    // Time flow
    if (g_Input.GetKeyState(GLFW_KEY_UP) == Input::KeyState::PRESSED
        || g_Input.GetKeyState(GLFW_KEY_RIGHT) == Input::KeyState::PRESSED) {
        m_TimeMultiplayersIndex = m_TimeMultiplayersIndex == m_TimeMultiplayers.size() - 1  ? m_TimeMultiplayersIndex : m_TimeMultiplayersIndex + 1;
        g_Time.TimeMultiplayer(m_TimeMultiplayers[m_TimeMultiplayersIndex]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_DOWN) == Input::KeyState::PRESSED
        || g_Input.GetKeyState(GLFW_KEY_LEFT) == Input::KeyState::PRESSED) {
        m_TimeMultiplayersIndex = m_TimeMultiplayersIndex == 0 ? 0 : m_TimeMultiplayersIndex - 1;
        g_Time.TimeMultiplayer(m_TimeMultiplayers[m_TimeMultiplayersIndex]);
    }
    
    // First person controller
    if (g_Input.GetKeyState(GLFW_KEY_W)
        || g_Input.GetKeyState(GLFW_KEY_S)
        || g_Input.GetKeyState(GLFW_KEY_A)
        || g_Input.GetKeyState(GLFW_KEY_D)) {
        m_TPC->Deactivate();
        m_FPC->Activate();
    }
    
    // Third person controller
    if (g_Input.GetKeyState(GLFW_KEY_0) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[0]);
        m_TPC->Radius(m_Radiuses[0]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_1) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[1]);
        m_TPC->Radius(m_Radiuses[1]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_2) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[2]);
        m_TPC->Radius(m_Radiuses[2]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_3) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[3]);
        m_TPC->Radius(m_Radiuses[3]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_4) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[4]);
        m_TPC->Radius(m_Radiuses[4]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_5) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[5]);
        m_TPC->Radius(m_Radiuses[5]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_6) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[6]);
        m_TPC->Radius(m_Radiuses[6]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_7) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[7]);
        m_TPC->Radius(m_Radiuses[7]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_8) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_TPC->Target(m_Planets[8]);
        m_TPC->Radius(m_Radiuses[8]);
    }
}
