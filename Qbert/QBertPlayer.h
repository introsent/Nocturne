#pragma once
#include "Component.h"
#include "AnimationComponent.h"
#include "Level.h"
#include "TranslationComponent.h"

class QBertPlayer : public dae::Component {
public:
    QBertPlayer(dae::GameObject* owner, Level* level);

    void Update(float deltaTime) override;
    bool TryMove(const glm::ivec2& direction);
    void JumpTo(const glm::ivec2& targetGridPos);

    // State getters
    bool IsJumping() const { return m_IsJumping; }
    glm::ivec2 GetGridPosition() const { return m_CurrentGridPos; }

private:
    void UpdateSpriteDirection(const glm::ivec2& direction);
    void CompleteJump();

    Level* m_pLevel;
    glm::ivec2 m_CurrentGridPos;
    glm::vec3 m_JumpStartPos;
    glm::vec3 m_JumpTargetPos;

    const float m_JumpDuration = 0.3f;  // Time to complete jump in seconds
    const float m_JumpHeight = 5.f;
    float m_JumpProgress{ 0.f };
    bool m_IsJumping{ false };

    AnimationComponent* m_pAnimation;
    //dae::TranslationComponent* m_pTranslation;
};

