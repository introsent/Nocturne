#pragma once
#include "Enemy.h"
#include <memory>
#include <functional>
#include "Directions.h"
#include "SpawningState.h"

class CoilyState;

class Coily : public Enemy
{
public:
    Coily(dae::GameObject* owner, glm::ivec2 spawnGridPosition, Level* level, const IPositionProxy& qbertPositionProxy);
    void Update(float deltaTime) override;

    void TransitionTo(std::unique_ptr<CoilyState> newState);
    void SetPlayerControlled(bool controlled) { m_isPlayerControlled = controlled; }
    bool IsPlayerControlled() const { return m_isPlayerControlled; }
    void HandleInput(const glm::ivec2& direction);
    glm::ivec2 GetDesiredSpawnGridPosition() const { return m_desiredSpawnGridPosition; }
    glm::ivec2 GetCurrentLookAtDirection() const { return m_currentDirection; }

private:
    std::unique_ptr<CoilyState> m_currentState{ std::make_unique<SpawningState>(GetOwner()) };
    glm::ivec2 m_desiredSpawnGridPosition{};
    bool m_isPlayerControlled{ false };
};