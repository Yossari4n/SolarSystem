#ifndef ILighSource_h
#define ILighSource_h

#include "ShaderProgram.h"

class ILighSource {
public:
    virtual void SetLightProperties(const ShaderProgram& shader) = 0;
};

#endif
