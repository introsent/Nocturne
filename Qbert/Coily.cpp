#include "Coily.h"
#include "Directions.h"

void Coily::UpdateAnimation(int frame)
{  
    m_pAnimation->SetFrame(frame);  
}

Coily::Coily(dae::GameObject* owner, Level* level, QBertPlayer* qbert) : Enemy(owner, level), m_pQBert(qbert) 
{
    m_pAnimation = owner->GetComponent<AnimationComponent>();
}

void Coily::Update(float deltaTime)
{
    if (m_currentState) {
        if (auto newState = m_currentState->Update(this, deltaTime)) {
            TransitionTo(std::move(newState));
        }
    }
}

void Coily::TransitionTo(std::unique_ptr<CoilyState> newState)
{
    if (m_currentState) {
        m_currentState->Exit(this);
    }

    m_currentState = std::move(newState);

    if (m_currentState) {
        m_currentState->Enter(this);
    }
}

    
