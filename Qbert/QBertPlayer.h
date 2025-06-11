#pragma once
#include "Component.h"
#include "QBertState.h"
#include <memory>
#include "Event.h"

class Level;
class AnimationComponent;

class QBertPlayer : public dae::Component {
public:
    QBertPlayer(dae::GameObject* owner, Level* level);

    void Update(float deltaTime) override;
    void HandleInput(const glm::ivec2& direction);

    void TransitionTo(std::unique_ptr<QBertState> newState);

    void MoveTo(const glm::ivec2& gridPos);
    void LookAt(const glm::ivec2& direction);

    void UpdateAnimation();
    void Respawn();

    Level* GetLevel() const { return m_pLevel; }
    glm::ivec2 GetGridPosition() const { return m_currentGridPos; }
    bool IsAcceptingInput() const { return m_pCurrentState ? m_pCurrentState->CanAcceptInput() : false; }

    bool TakeHit();

    Event<const glm::ivec2&> OnPositionChanged;
private:
    std::unique_ptr<QBertState> m_pCurrentState;
    Level* m_pLevel;
    glm::ivec2 m_currentGridPos{};
    glm::ivec2 m_currentDirection{};
    AnimationComponent* m_pAnimation = nullptr;
};