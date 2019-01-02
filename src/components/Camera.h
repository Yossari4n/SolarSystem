#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "IComponent.h"
#include "../utilities/Time.h"
#include "../utilities/Input.h"

#include <iostream>
#include <string>

class Camera : public IComponent {
public:
    Camera(glm::mat4 projection, glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f));
    ~Camera();
    
    void Initialize() override;
    void Update() override;
    
    glm::mat4 ViewMatrix() const;
    
    const glm::mat4& Projection() const { return m_Projection; }
    const glm::vec3& Front() const { return m_Front; }
    const glm::vec3& WorldUp() const { return m_WorldUp; }
    
    const glm::vec3& Position() const { return m_Position; }
    const glm::vec3& Up() const { return m_Up; }
    const glm::vec3& Right() const { return m_Right; }
    
private:
    glm::mat4 m_ViewMatrix;
    
    glm::mat4 m_Projection;
    
    glm::vec3 m_WorldUp;
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
};
