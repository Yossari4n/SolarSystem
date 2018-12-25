#ifndef IComponent_h
#define IComponent_h

#include <iostream>

#include "Object.h"

class Object;

class IComponent {
    friend class Object;

public:
    virtual ~IComponent() { std::cout << "Dest comp\n"; };
    
    virtual void Initialize() {};
    virtual void Update() {};
    virtual void Destroy() {};
    
    Object& Object();
    
private:
    class Object *m_Object;
};

#endif
