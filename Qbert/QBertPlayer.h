#pragma once
#include "Component.h"
#include "QBertState.h"
#include <memory>

class QBertState;
class Level;
class AnimationComponent;

class QBertPlayer : public dae::Component {
public:
    QBertPlayer(dae::GameObject* owner, Level* level);

    void Update(float deltaTime) override;
    void Render() const override {}

	// Position management
    glm::vec3 GetCurrentPosition() const { return GetOwner()->GetWorldPosition(); }
    void SetPosition(const glm::vec3& pos) { GetOwner()->SetLocalPosition(pos); }

    // State management
    void ChangeState(std::unique_ptr<QBertState> newState);
    void Die();
    void Respawn();

    // Getters
    AnimationComponent* GetAnimation() const { return m_pAnimation; }
    float GetJumpDuration() const { return m_JumpDuration; }
    float GetJumpHeight() const { return m_JumpHeight; }
    glm::vec3 GetJumpTargetPos() const { return m_JumpTargetPos; }
    int GetDeathFrame() { return 3; }
    glm::ivec2 GetCurrentDirection() const { return m_CurrentDirection; }


    // State handling
    bool CanAcceptInput() const {
        return m_pCurrentState->GetName() == "Idle";
    }
    QBertState* GetState() const { return m_pCurrentState.get(); }

    // Movement
    bool TryStartJump(const glm::ivec2& direction);
    void CompleteJump();
    void UpdateSpriteDirection(const glm::ivec2& direction);

private:
    friend class QBertState;


    std::unique_ptr<QBertState> m_pCurrentState;
    AnimationComponent* m_pAnimation;
    Level* m_pLevel;

    glm::ivec2 m_CurrentGridPos{ 0,0 };
    glm::ivec2 m_CurrentDirection{ 0,0 };
    glm::vec3 m_JumpTargetPos;

    const float m_JumpDuration{ 0.4f };
    const float m_JumpHeight{ 5.f };
};