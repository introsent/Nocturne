#include "Coily.h"
#include "Directions.h"
#include "utils.h"

Coily::Coily(dae::GameObject* owner, glm::ivec2 spawnGridPosition, Level* level, const IPositionProxy& qbertPositionProxy) :
    Enemy(owner, level, qbertPositionProxy, [this](const glm::ivec2& grid) { return GridToWorldCoily(grid); }),
    m_desiredSpawnGridPosition(spawnGridPosition)
{
    m_currentState->Enter(this);
}

void Coily::Update(float deltaTime)
{
    if (m_currentState) {
        if (auto newState = m_currentState->Update(this, deltaTime)) {
            TransitionTo(std::move(newState));
        }
    }
    Enemy::Update(deltaTime);
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

void Coily::HandleInput(const glm::ivec2& direction)
{
    if (m_isPlayerControlled && m_currentState) {
        m_currentState->HandleInput(this, direction);
    }
}