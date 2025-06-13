#pragma once
#include "Component.h"
#include "QBertState.h"
#include <memory>
#include "Event.h"
#include "HealthComponent.h"
#include "Directions.h"

class Level;
class AnimationComponent;

class QBertPlayer : public dae::Component {
public:
    QBertPlayer(dae::GameObject* owner, Level* level, HealthComponent* healthComponent, glm::ivec2 spawnGridPosition);
    void Update(float deltaTime) override;

    void HandleInput(const glm::ivec2& direction);
    void MoveTo(const glm::ivec2& gridPos);
    void LookAt(const glm::ivec2& direction);
    bool IsAcceptingInput() const { return m_pCurrentState && m_pCurrentState->CanAcceptInput(); }
    bool TakeHit();
    void ReduceHealth();
    void Respawn();
    glm::ivec2 GetGridPosition() const { return m_currentGridPos; }

    void UpdateAnimation();

	Level* GetLevel() const { return m_pLevel; }
    Event<const glm::ivec2&> OnPositionChanged;

private:
    void TransitionTo(std::unique_ptr<QBertState> newState);
;

    Level* m_pLevel{};
    std::unique_ptr<QBertState> m_pCurrentState{};
    AnimationComponent* m_pAnimation{};
    glm::ivec2 m_currentGridPos{ 0, 0 };
    glm::ivec2 m_currentDirection{ DOWN_RIGHT };
    HealthComponent* m_pHealth{};
    bool m_isDead{ false };
    float m_respawnTimer{ 0.f };
};