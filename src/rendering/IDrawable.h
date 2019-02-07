#ifndef IDrawable_h
#define IDrawable_h

#include "ShaderProgram.h"

class IDrawable {
public:
    virtual void Draw(const ShaderProgram &shader) const = 0;
    
    ShaderProgram::TYPE ShaderType() const { return m_ShaderType; }
    void ShaderType(ShaderProgram::TYPE type) { m_ShaderType = type; }
    
protected:
    ShaderProgram::TYPE m_ShaderType;
};

#endif
