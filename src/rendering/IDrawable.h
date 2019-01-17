#ifndef IDrawable_h
#define IDrawable_h

#include "ShaderProgram.h"

class IDrawable {
public:
    enum ShaderTypes {
        COLOR_PURE = 0,
        COLOR_LIGHT_RECEIVER,
        TEXTURE_PURE,
        TEXTURE_LIGHT_RECEIVER,
        
        COUNT
    };
    
    virtual void Draw(const ShaderProgram &shader) const = 0;
    
    ShaderTypes ShaderType() const { return m_ShaderType; }
    
protected:
    ShaderTypes m_ShaderType;
};

#endif
