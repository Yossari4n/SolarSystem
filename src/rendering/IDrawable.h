#ifndef IDrawable_h
#define IDrawable_h

#include "ShaderProgram.h"

class IDrawable {
public:
    // Enum used as indicies, don't change numeration or order
    enum ShaderTypes {
        LIGHT_SOURCE = 0,
        LIGHT_RECEIVER,
        
        COUNT
    };
    
    virtual void Draw(const ShaderProgram &shader) const = 0;
    
    ShaderTypes ShaderType() const { return m_ShaderType; }
    
protected:
    ShaderTypes m_ShaderType;
};

#endif
