#ifndef Tail_h
#define Tail_h

#include "IComponent.h"
#include "../../rendering/IDrawable.h"
#include "../../utilities/Time.h"

#include <deque>

class Line;

class Tail : public IComponent, public IDrawable {
public:
    Tail(float lenght, glm::vec3 color);
    
    void Initialize() override;
    void OnActivate() override;
    void Update() override;
    void OnDeactivate() override;
    void Destroy() override;
    
    void Draw(const ShaderProgram& shader) const override;
    
private:
    float m_MaxLength;
    glm::vec3 m_Color;
    std::deque<Line*> m_Lines;
    
    float m_CurrentLength;
    glm::vec3 m_LastPosition;
};

#endif
