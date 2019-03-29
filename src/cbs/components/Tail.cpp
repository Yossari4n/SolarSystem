#include "Tail.h"
#include "../../utilities/Line.h"

Tail::Tail(float length, glm::vec3 color)
    : m_MaxLength(length)
    , m_Color(color) {
    m_ShaderType = ShaderProgram::Type::PURE_COLOR;
        
    m_CurrentLength = 0.0f;
}

void Tail::Initialize() {
    Object().Scene().RegisterDrawCall(this);
    m_LastPosition = Object().Transform().Position();
}

void Tail::OnActivate() {
    Object().Scene().RegisterDrawCall(this);
    m_LastPosition = Object().Transform().Position();
}

void Tail::Update() {
    if (!m_Active || g_Time.TimeMultiplayer() == 0.0f) {
        return;
    }
    
    glm::vec3 curr_pos = Object().Transform().Position();
    
    m_Lines.push_back(new Line(curr_pos, m_LastPosition, m_Color));
    
    m_CurrentLength += g_Time.DeltaTime();
    if (m_CurrentLength > m_MaxLength) {
        delete (*m_Lines.begin());
        m_Lines.pop_front();
    }
    
    m_LastPosition = curr_pos;
}

void Tail::OnDeactivate() {
    Object().Scene().UnregisterDrawCall(this);
    
    for (auto it = m_Lines.begin(); it != m_Lines.end(); ++it) {
        delete (*it);
    }
    m_Lines.clear();
    m_CurrentLength = 0;
}

void Tail::Destroy() {
    Object().Scene().UnregisterDrawCall(this);
    
    for (auto it = m_Lines.begin(); it != m_Lines.end(); ++it) {
        delete (*it);
    }
    m_Lines.clear();
    m_CurrentLength = 0;
}

void Tail::Draw(const ShaderProgram &shader) const {
    glm::vec3 color_step = m_Color / (float)m_Lines.size();
    glm::vec3 current_color = color_step;
    
    for (auto it = m_Lines.begin(); it != m_Lines.end(); ++it) {
        (*it)->Color(current_color);
        (*it)->Draw(shader);
        
        current_color = current_color + color_step;
    }
}
