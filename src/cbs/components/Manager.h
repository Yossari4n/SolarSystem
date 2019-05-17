#ifndef Manager_h
#define Manager_h

#include "IComponent.h"
#include "FirstPersonController.h"
#include "ThirdPersonController.h"

#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

#include <array>

class Manager : public IComponent {
public:
    Manager(std::array<class Object *, 9> planets, FirstPersonController* fpc, ThirdPersonController* tpc);
    
    void Initialize() override;
    void Update() override;
    
private:
    // Drawing mode
    bool m_Realistic;
    
    // Camera controllers
    FirstPersonController* m_FPC;
    ThirdPersonController* m_TPC;
    
    // Time
    bool m_Paused;
    unsigned int m_TimeMultiplayersIndex;
    std::array<int, 5> m_TimeMultiplayers;
    
    // Planets
    int m_CurrentPlanetIndex;
    std::array<class Object*, 9> m_Planets;
    std::array<float, 9> m_Radiuses;
};

#endif
