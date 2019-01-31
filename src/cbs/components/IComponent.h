#ifndef IComponent_h
#define IComponent_h

class Object;

class IComponent {
    friend class Object;

public:
    IComponent()
        : m_Object(nullptr)
        , m_Active(true) {}
    
    virtual ~IComponent() {}
    
    Object& Object() const {
        return *m_Object;
    }
    
    void Activate() {
        m_Active = true;
    }
    
    void Deactivate() {
        m_Active = false;
    }

protected:
    virtual void Initialize() {};
    virtual void Update() {};
    virtual void Destroy() {};
    
    bool m_Active;

private:
    class Object* m_Object;
};

#include "Object.h"

#endif
