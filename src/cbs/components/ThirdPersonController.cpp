#include "ThirdPersonController.h"

ThirdPersonController::ThirdPersonController(class Object* target, float radius, glm::vec3 front, float mouse_sensitivity)
    : m_Target(&target->Transform())
    , m_Radius(radius)
    , m_Front(front)
    , m_MouseSensitivity(mouse_sensitivity) {
    m_XRotation = 0.0f;
    m_YRotation = 0.0f;
    m_RotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
}

void ThirdPersonController::Radius(float radius) {
    if (radius < 0.0f) {
        radius = 0.0f;
    }
    
    m_Radius = radius;
}

void ThirdPersonController::OnActivate() {
    m_XRotation = 0.0f;
    m_YRotation = 0.0f;
    m_RotationAxis = glm::vec3(-1.0f, 0.0f, 0.0f);
}

void ThirdPersonController::Update() {
    if (!m_Active) {
        return;
    }
    
    // Get mouse input and accumulate it as rotations
    m_XRotation += glm::radians(g_Input.MouseOffset().y * m_MouseSensitivity);
    m_YRotation += glm::radians(g_Input.MouseOffset().x * m_MouseSensitivity);

    // Prevent object flip by keeping m_XRotation beetwen <-60, 60> degrees
    if (m_XRotation > DEGREES_60) {
        m_XRotation = DEGREES_60;
    } else if (m_XRotation < -DEGREES_60) {
        m_XRotation = -DEGREES_60;
    }
    
    // Get whole rotation around Y
    glm::quat rot_y(glm::vec3(0.0f, m_YRotation, 0.0f));
    
    // Create new arbitrary X axis
    glm::vec3 curr_rotation_axis = m_RotationAxis * rot_y;
    
    // Rotate camera around world origin and then move it to m_Target
    glm::vec3 new_pos = glm::vec3(0.0f, 0.0f, m_Radius) * rot_y;
    new_pos = glm::rotate(new_pos, m_XRotation, curr_rotation_axis);
    new_pos = new_pos + m_Target->Position();
    
    // Calculate rotation from old front to new front
    glm::vec3 diff = m_Target->Position() - new_pos;
    glm::quat front_rot = m_RotationBeetwen(m_Front, diff);
    
    // Apply
    Object().Transform().Position(new_pos);
    Object().Transform().Rotation(front_rot);
}

glm::quat ThirdPersonController::m_RotationBeetwen(const glm::vec3 &start, const glm::vec3 &dest) {
    glm::vec3 n_start = glm::normalize(start);
    glm::vec3 n_dest = glm::normalize(dest);
    
    float cos_theta = glm::dot(n_start, n_dest);
    glm::vec3 rotation_axis;
    
    if (cos_theta < -1 + 0.001f) {
        rotation_axis = cross(glm::vec3(0.0f, 0.0f, 1.0f), n_start);
        if (length2(rotation_axis) < 0.01) {
            rotation_axis = cross(glm::vec3(1.0f, 0.0f, 0.0f), n_start);
        }
        
        rotation_axis = normalize(rotation_axis);
        return glm::angleAxis(glm::radians(180.0f), rotation_axis);
    }
    
    rotation_axis = cross(n_start, n_dest);
    
    float s = sqrt((1 + cos_theta) * 2);
    float invs = 1 / s;
    
    return glm::quat(s * 0.5f, rotation_axis.x * invs, rotation_axis.y * invs, rotation_axis.z * invs);
}
