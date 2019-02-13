#ifndef Cubemap_h
#define Cubemap_h

#include "../rendering/IDrawable.h"

#include <stb/stb_image.h>

#include <string>

class Cubemap : public IDrawable {
public:
    Cubemap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back, ShaderProgram::Type type);
    
    void Draw(const ShaderProgram& shader) const override;
    
private:
    unsigned int m_ID;
    unsigned int m_VAO;
    unsigned int m_VBO;
    
    void m_Load(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
    void m_Initialize();
};

#endif
