#include "Line.h"

Line::Line(glm::vec3 start, glm::vec3 end, glm::vec3 color, float width)
    : m_Start(start)
    , m_End(end)
    , m_Color(color)
    , m_Width(width) {
    m_ShaderType = ShaderProgram::TYPE::COLOR_PURE;
    
    float vertices[] = { start.x, start.y, start.z, end.x, end.y, end.z };
    
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    glBindVertexArray(m_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Line::~Line() {
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Line::Draw(const ShaderProgram &shader) const {
    glm::mat4 model(1.0f);
    shader.SetMat4("model", model);
    shader.SetVec3("color", m_Color);
    
    glBindVertexArray(m_VAO);
    glLineWidth(m_Width);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}
