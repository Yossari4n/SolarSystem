#ifndef FirstPersonController_h
#define FirstPersonController_h

#include "IComponent.h"
#include "Camera.h"
#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

#define DEGREES_60 (60.0f * 3.14f / 180.0f)

class FirstPersonController : public IComponent {
public:
    FirstPersonController(float movement_speed_fast = 50.0f, float movement_speed_slow = 1.0f, float mouse_sensitivity = 0.1f, glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f));
    
    void Initialize() override;
    void OnActivate() override;
    void Update() override;
    
private:
    float m_CurrentMovementSpeed;
    float m_MovementSpeedFast;
    float m_MovementSpeedSlow;
    float m_MouseSensitivity;
    float m_XRotation;
    
    glm::vec2 m_LastMousePos;
    
    glm::vec3 m_WorldUp;
    glm::vec3 m_Front;
    glm::vec3 m_Right;
    
    Transform* m_Transform;
};

#endif
