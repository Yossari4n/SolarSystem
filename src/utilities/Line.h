#ifndef Line_h
#define Line_h

#include "../rendering/IDrawable.h"

class Line : public IDrawable {
public:
    Line(glm::vec3 start, glm::vec3 end, glm::vec3 color, float width = 1.0f);
    
    void Draw(const ShaderProgram& shader) const override;
    
private:
    glm::vec3 m_Start;
    glm::vec3 m_End;
    glm::vec3 m_Color;
    float m_Width;
    
    unsigned int m_VAO;
    unsigned int m_VBO;
};

#endif
