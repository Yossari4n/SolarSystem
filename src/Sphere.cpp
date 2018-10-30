#include "Sphere.h"

unsigned int Sphere::m_VAO = 0;
unsigned int Sphere::m_VBO = 0;
unsigned int Sphere::m_EBO = 0;
unsigned int Sphere::m_VerticesCount = 0;

Sphere::Sphere()
    : m_Position(glm::vec3(0.0f))
    , m_Rotation(glm::vec3(0.0f))
    , m_Scale(glm::vec3(1.0f)){
}

Sphere::~Sphere() {
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Sphere::Init() {
    float lats = 40;
    float longs = 40;
    
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    int indicator = 0;
    for(int i = 0; i <= lats; i++) {
        double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);
        
        double lat1 = glm::pi<double>() * (-0.5 + (double)i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
        
        for(int j = 0; j <= longs; j++) {
            double lng = 2 * glm::pi<double>() * (double)(j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);
            
            vertices.push_back(x * zr0);
            vertices.push_back(y * zr0);
            vertices.push_back(z0);
            indices.push_back(indicator);
            indicator++;
            
            vertices.push_back(x * zr1);
            vertices.push_back(y * zr1);
            vertices.push_back(z1);
            indices.push_back(indicator);
            indicator++;
        }
        
        indices.push_back(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    }
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    
    m_VerticesCount = static_cast<unsigned int>(indices.size());
}

void Sphere::Draw(const ShaderProgram& shader_program) const {
    shader_program.Use();
    shader_program.SetMat4("model", m_Model);
    shader_program.SetVec4("Color", m_Color);
    
    glBindVertexArray(m_VAO);glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    glPrimitiveRestartIndex(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glDrawElements(GL_TRIANGLE_STRIP, m_VerticesCount, GL_UNSIGNED_INT, NULL);
}

void Sphere::Position(const glm::vec3& position) {
    m_Position = position;
    
    UpdateModel();
}

void Sphere::Rotation(const glm::vec3& rotation) {
    m_Rotation = rotation;
    
    UpdateModel();
}

void Sphere::Scale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

void Sphere::UpdateModel() {
    m_Model = glm::translate(glm::mat4(), m_Position);
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_Model = glm::scale(m_Model, m_Scale);
}
