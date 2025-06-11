#include "Coily.h"
#include "Directions.h"

Coily::Coily(dae::GameObject* owner, glm::ivec2 spawnGridPosition, Level* level, const IPositionProxy& qbertPositionProxy) :
    Enemy(owner, level, qbertPositionProxy),
	m_desiredSpawnGridPosition(spawnGridPosition)
{
    m_pAnimation = owner->GetComponent<AnimationComponent>();
    m_currentState.get()->Enter(this);
}

void Coily::UpdateAnimation(int frame)
{  
    m_pAnimation->SetFrame(frame);  
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

    
