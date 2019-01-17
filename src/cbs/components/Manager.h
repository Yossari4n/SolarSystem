#ifndef Manager_h
#define Manager_h

#include "IComponent.h"
#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

class Manager : public IComponent {
public:
    Manager();
    
    void Initialize() override;
    void Update() override;
    
private:
    bool m_Paused;
    int m_TimeMultiplayersIndex;
    std::array<int, 5> m_TimeMultiplayers;
};

#endif
