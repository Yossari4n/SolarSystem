#ifndef IDrawable_h
#define IDrawable_h

#include "ShaderProgram.h"

class IDrawable {
    friend class DrawManager;
    
public:
    enum ShaderType {
        LIGHT_SOURCE = 0,
        LIGHT_RECEIVER,
        
        COUNT
    };
    
    virtual void Draw(const ShaderProgram &shader) = 0;

protected:
    ShaderType m_ShaderType;
};

#endif
