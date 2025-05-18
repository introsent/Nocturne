#pragma once
#include "Component.h"
#include "QBertState.h"
#include <memory>

class Level;
class AnimationComponent;

class QBertPlayer : public dae::Component {
public:
    QBertPlayer(dae::GameObject* owner, Level* level);

    void Update(float deltaTime);

    // State management
    void ChangeState(std::unique_ptr<QBertState> newState);
    QBertState* GetCurrentState() const { return m_pCurrentState.get(); }

    // Getters
    Level* GetLevel() const { return m_pLevel; }
    const glm::ivec2& GetCurrentGridPos() const { return m_CurrentGridPos; }
    const glm::vec3& GetJumpTargetPos() const { return m_JumpTargetPos; }
    float GetJumpDuration() const { return m_JumpDuration; }
    float GetJumpHeight() const { return m_JumpHeight; }
    glm::ivec2 GetCurrentDirection() const { return m_CurrentDirection; }

    // Setters
    void SetPosition(const glm::vec3& pos) { GetOwner()->SetLocalPosition(pos); }
    void SetCurrentGridPos(const glm::ivec2& pos) { m_CurrentGridPos = pos; }
    void SetJumpTargetPos(const glm::vec3& pos) { m_JumpTargetPos = pos; }
    void SetCurrentDirection(const glm::ivec2& dir) { m_CurrentDirection = dir; }

    bool CanAcceptInput() const;

    void UpdateSpriteDirection(const glm::ivec2& direction) const;
    void Die();
    void Respawn();

private:
    std::unique_ptr<QBertState> m_pCurrentState;
    Level* m_pLevel;
    glm::ivec2 m_CurrentGridPos{};
    glm::vec3 m_JumpTargetPos{};
    glm::ivec2 m_CurrentDirection{};
    float m_JumpDuration = 0.5f;
    float m_JumpHeight = 32.f;
    AnimationComponent* m_pAnimation;
};