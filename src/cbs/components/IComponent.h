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
        OnActivate();
    }
    
    void Deactivate() {
        m_Active = false;
        OnDeactivate();
    }

protected:
    virtual void Initialize() {};
    virtual void OnActivate() {};
    virtual void Update() {};
    virtual void OnDeactivate() {};
    virtual void Destroy() {};
    
    bool m_Active;

private:
    class Object* m_Object;
};

#include "Object.h"

#endif
