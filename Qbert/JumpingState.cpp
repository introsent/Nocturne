#include "JumpingState.h"
#include <numbers>
#include "QBertPlayer.h"
#include "Level.h"
#include "IdleState.h"

void JumpingState::Enter(dae::GameObject* player) {
    QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
    if (!qbertPlayer) return;

    m_JumpProgress = 0.f;
    m_JumpStartPos = player->GetWorldPosition();
    qbertPlayer->UpdateSpriteDirection(qbertPlayer->GetCurrentDirection());
}

void JumpingState::Update(dae::GameObject* player, float deltaTime) {
    QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
    if (!qbertPlayer) return;

    m_JumpProgress += deltaTime / qbertPlayer->GetJumpDuration();
    const float t = std::clamp(m_JumpProgress, 0.0f, 1.0f);

    // Smooth jump curve calculation
    const float yOffset = sinf(t * std::numbers::pi_v<float>) * qbertPlayer->GetJumpHeight();
    const glm::vec3 newPos = glm::mix(
        m_JumpStartPos,
        qbertPlayer->GetJumpTargetPos(),
        t
    );

    qbertPlayer->SetPosition({ newPos.x, newPos.y - yOffset, newPos.z });

    if (m_JumpProgress >= 1.0f) {
        qbertPlayer->SetPosition(qbertPlayer->GetJumpTargetPos());
        qbertPlayer->ChangeState(std::make_unique<IdleState>());
        qbertPlayer->GetLevel()->HandleJump(qbertPlayer->GetCurrentGridPos());
    }
}