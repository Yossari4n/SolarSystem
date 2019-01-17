#ifndef IComponent_h
#define IComponent_h

#include "Object.h"

class IComponent {
    friend class Object;

public:
    virtual ~IComponent() {}
    
    virtual void Initialize() {};
    virtual void Update() {};
    virtual void Destroy() {};
    
    
    Object& Object() const {
        return *m_Object;
    }
    
private:
    class Object* m_Object;
};

#endif
