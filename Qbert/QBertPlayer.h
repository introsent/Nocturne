#pragma once
#include "Component.h"
#include "QBertState.h"
#include <memory>

class QBertState;
class Level;
class AnimationComponent;

///
/// QBert player controller component handling movement, state and animations
///
class QBertPlayer : public dae::Component {
public:
    QBertPlayer(dae::GameObject* owner, Level* level);

    void Update(float deltaTime) override;
    void Render() const override {}

    // --- Position Management ---
    glm::vec3 GetCurrentPosition() const { return GetOwner()->GetWorldPosition(); }
    void SetPosition(const glm::vec3& pos) { GetOwner()->SetLocalPosition(pos); }

    // --- State Management ---
    void ChangeState(std::unique_ptr<QBertState> newState);
    void Die();         // Handle player death sequence
    void Respawn();     // Reset player to starting position

    // --- Getters ---
    AnimationComponent* GetAnimation() const { return m_pAnimation; }
    float GetJumpDuration() const { return m_JumpDuration; }
    float GetJumpHeight() const { return m_JumpHeight; }
    glm::vec3 GetJumpTargetPos() const { return m_JumpTargetPos; }
    int GetDeathFrame() { return 3; } // Frame 3 contains death animation
    glm::ivec2 GetCurrentDirection() const { return m_CurrentDirection; }

    // --- Input Handling ---
    bool CanAcceptInput() const {
        return m_pCurrentState->GetName() == "Idle";
    }
    QBertState* GetState() const { return m_pCurrentState.get(); }

    // --- Movement System ---
    bool TryStartJump(const glm::ivec2& direction); // Attempt to initiate jump
    void CompleteJump();                            // Finalize jump position
    void UpdateSpriteDirection(const glm::ivec2& direction) const; // Update animation frame based on move direction

private:
    friend class QBertState; // Allow state classes access to private members

    // --- Components & References ---
    std::unique_ptr<QBertState> m_pCurrentState;
    AnimationComponent* m_pAnimation;
    Level* m_pLevel;

    // --- Movement Properties ---
    glm::ivec2 m_CurrentGridPos{ 0,0 };      // Current grid position (logical position)
    glm::ivec2 m_CurrentDirection{ 0,0 };    // Last movement direction
    glm::vec3 m_JumpTargetPos;               // World position target for current jump

    // --- Jump Parameters ---
    const float m_JumpDuration{ 0.4f };  // Time to complete jump in seconds
    const float m_JumpHeight{ 5.f };     // Vertical arc height during jump
};