#ifndef FirstPersonController_h
#define FirstPersonController_h

#include "IComponent.h"
#include "Camera.h"
#include "../utilities/Time.h"
#include "../utilities/Input.h"

#include <iostream>

class FirstPersonController : public IComponent {
public:
    FirstPersonController(float movement_speed_fast = 50.0f, float movement_speed_slow = 1.0f, float mouse_sensivity = 0.1f, float pitch = 0.0f, float yaw = 0.0f, glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f));
    
    void Initialize() override;
    void Update() override;
    
private:
    float m_CurrentMovementSpeed;
    float m_MovementSpeedFast;
    float m_MovementSpeedSlow;
    float m_MouseSensivity;
    float m_Yaw;
    float m_Pitch;
    glm::vec3 m_WorldUp;
    
    glm::vec3 m_Front;
    glm::vec3 m_Right;
    
    glm::vec2 m_LastMousePos;
};

#endif
