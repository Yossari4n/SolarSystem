#include "IComponent.h"

void IComponent::Initialize() {}
void IComponent::Destroy() {}

void IComponent::RegisterUpdate()  {
    m_Object->RegisterUpdateCall(this);
}

void IComponent::UnregisterUpdate() {
    m_Object->UnregisterUpdateCall(this);
}

Object& IComponent::Object() {
    return *m_Object;
}
