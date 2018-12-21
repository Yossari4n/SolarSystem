#ifndef IComponent_h
#define IComponent_h

#include "Object.h"

class Object;

class IComponent {
    friend class Object;

public:
    virtual ~IComponent() {};
    
    virtual void Initialize() = 0;
    virtual void Update() {}
    virtual void Destroy() = 0;
    
    void RegisterUpdate();
    void UnregisterUpdate();
    Object& Object();
    
private:
    class Object *m_Object;
};

#endif
