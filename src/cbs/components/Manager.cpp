#include "Manager.h"

#include "MeshRenderer/MeshRenderer.h"
#include "Tail.h"

Manager::Manager(std::array<class Object*, 9> planets, FirstPersonController* fpc, ThirdPersonController* tpc)
    : m_Planets(planets)
    , m_FPC(fpc)
    , m_TPC(tpc)
    , m_TimeMultiplayers({ 1, 2, 4, 10, 50 })
    , m_Radiuses({100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 10.0f, 10.0f, 10.0f, 10.0f}) {
    
    m_CurrentPlanetIndex = -1;
        
    m_Paused = false;
    m_TimeMultiplayersIndex = 0;
        
    m_Realistic = true;
}

void Manager::Initialize() {
    g_Time.TimeMultiplayer(m_TimeMultiplayers[0]);
    m_TPC->Deactivate();
    
    for (auto it = m_Planets.begin() + 1; it != m_Planets.end(); ++it) {
        (*it)->GetComponent<Tail>()->Deactivate();
    }
}

void Manager::Update() {
    if (g_Input.GetKeyState(GLFW_KEY_Z) == Input::PRESSED) {
        std::cout << Object().Transform().Position().x << ' ' << Object().Transform().Position().y << ' ' << Object().Transform().Position().z << '\n';
    }
    
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
            g_Time.TimeMultiplayer(0);
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
    
    // Drawin mode
    if (g_Input.GetKeyState(GLFW_KEY_TAB) == Input::KeyState::PRESSED) {
        if (m_Realistic) {
            m_Realistic = false;
            
            for (auto it = m_Planets.begin() + 1; it != m_Planets.end(); ++it) {
                (*it)->GetComponent<MeshRenderer>()->ShaderType(ShaderProgram::Type::PURE_TEXTURE);
                (*it)->GetComponent<Tail>()->Activate();
            }
        } else {
            m_Realistic = true;
            
            for (auto it = m_Planets.begin() + 1; it != m_Planets.end(); ++it) {
                (*it)->GetComponent<MeshRenderer>()->ShaderType(ShaderProgram::Type::PHONG);
                (*it)->GetComponent<Tail>()->Deactivate();
            }
        }
    }
    
    // First person controller
    if (!m_FPC->Active()
        && (g_Input.GetKeyState(GLFW_KEY_W)
            || g_Input.GetKeyState(GLFW_KEY_S)
            || g_Input.GetKeyState(GLFW_KEY_A)
            || g_Input.GetKeyState(GLFW_KEY_D))) {
        m_TPC->Deactivate();
        m_FPC->Activate();
        m_CurrentPlanetIndex = -1;
    }
    
    // Third person controller
    if (g_Input.GetKeyState(GLFW_KEY_0) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 0;
        m_TPC->Target(m_Planets[0]);
        m_TPC->Radius(m_Radiuses[0]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_1) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 1;
        m_TPC->Target(m_Planets[1]);
        m_TPC->Radius(m_Radiuses[1]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_2) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 2;
        m_TPC->Target(m_Planets[2]);
        m_TPC->Radius(m_Radiuses[2]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_3) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 3;
        m_TPC->Target(m_Planets[3]);
        m_TPC->Radius(m_Radiuses[3]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_4) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 4;
        m_TPC->Target(m_Planets[4]);
        m_TPC->Radius(m_Radiuses[4]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_5) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 5;
        m_TPC->Target(m_Planets[5]);
        m_TPC->Radius(m_Radiuses[5]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_6) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 6;
        m_TPC->Target(m_Planets[6]);
        m_TPC->Radius(m_Radiuses[6]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_7) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 7;
        m_TPC->Target(m_Planets[7]);
        m_TPC->Radius(m_Radiuses[7]);
    }
    if (g_Input.GetKeyState(GLFW_KEY_8) == Input::KeyState::PRESSED) {
        m_FPC->Deactivate();
        m_TPC->Activate();
        
        m_CurrentPlanetIndex = 8;
        m_TPC->Target(m_Planets[8]);
        m_TPC->Radius(m_Radiuses[8]);
    }
    
	// Scroll
    if (m_TPC->Active()) {
        float new_radius = m_TPC->Radius() - g_Input.ScrollOffset();
        if (new_radius < m_Radiuses[m_CurrentPlanetIndex]) {
            new_radius = m_Radiuses[m_CurrentPlanetIndex];
        }
        
        m_TPC->Radius(new_radius);
    }
}
