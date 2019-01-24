#include "Manager.h"

Manager::Manager()
    : m_Paused(false)
    , m_TimeMultiplayersIndex(0) {
    m_TimeMultiplayers = { 1, 2, 4, 10, 50 };
}

void Manager::Initialize() {
    g_Time.TimeMultiplayer(m_TimeMultiplayers[0]);
}

void Manager::Update() {
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
    if (g_Input.GetKeyState(GLFW_KEY_Z) == Input::KeyState::PRESSED) {
        g_Time.TimeMultiplayer(m_TimeMultiplayers[0]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_X) == Input::KeyState::PRESSED) {
        g_Time.TimeMultiplayer(m_TimeMultiplayers[1]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_C) == Input::KeyState::PRESSED) {
        g_Time.TimeMultiplayer(m_TimeMultiplayers[2]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_V) == Input::KeyState::PRESSED) {
        g_Time.TimeMultiplayer(m_TimeMultiplayers[3]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_B) == Input::KeyState::PRESSED) {
        g_Time.TimeMultiplayer(m_TimeMultiplayers[4]);
    }
}
