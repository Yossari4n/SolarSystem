#include "Time.h"

Time::Time()
    : m_DeltaTime(0.0f)
    , m_FixedDeltaTime(0.0f)
    , m_LastFrame(0.0f)
    , m_TimeMultiplier(1.0f) {
    m_CurrentTime = glfwGetTime();
    m_FixedCurrentTime = m_CurrentTime;
}

void Time::Update() {
    m_CurrentTime = glfwGetTime();
    
    // Absolute time calculations
    m_DeltaTime = m_CurrentTime - m_LastFrame;
    m_LastFrame = m_CurrentTime;
    
    // Relative time calculations
    m_FixedDeltaTime = m_DeltaTime * m_TimeMultiplier;
    m_FixedCurrentTime +=  m_FixedDeltaTime;
}

void Time::TimeMultiplayer(float time_multiplayer) {
    if (time_multiplayer < 0.0f) {
        time_multiplayer = 1.0f;
    }
    
    m_TimeMultiplier = time_multiplayer;
}
