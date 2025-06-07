#pragma once
#include "Component.h"
#include "QBertState.h"
#include <memory>

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
    glm::ivec2 GetGridPosition() const { return m_CurrentGridPos; }
    bool IsAcceptingInput() const { return m_pCurrentState ? m_pCurrentState->CanAcceptInput() : false; }
private:
    std::unique_ptr<QBertState> m_pCurrentState;
    Level* m_pLevel;
    glm::ivec2 m_CurrentGridPos{};
    glm::ivec2 m_CurrentDirection{};
    AnimationComponent* m_pAnimation = nullptr;
};