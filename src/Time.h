#ifndef Time_h
#define Time_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Time {
public:
    Time();
    
    void Update();
    
    float CurrentTime() const { return m_CurrentTime; }
    float FixedCurrentTime() const { return m_FixedCurrentTime; }
    float DeltaTime() const { return m_DeltaTime; }
    float FixedDeltaTime() const { return m_FixedDeltaTime; }
    
    float TimeMultiplayer() const { return m_TimeMultiplier; }
    void TimeMultiplayer(float time_multiplayer);
    
private:
    float m_CurrentTime;
    float m_FixedCurrentTime;
    float m_DeltaTime;
    float m_FixedDeltaTime;
    float m_TimeMultiplier;
    
    float m_LastFrame;
};

extern Time g_Time;

#endif
