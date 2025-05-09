#include "JumpingState.h"
#include <numbers>
#include "QBertPlayer.h"

#include "IdleState.h"

void JumpingState::Enter(dae::GameObject* player) {
    QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
    if (!qbertPlayer) return;

    m_JumpProgress = 0.f;
    m_JumpStartPos = qbertPlayer->GetCurrentPosition();
    qbertPlayer->UpdateSpriteDirection(qbertPlayer->GetCurrentDirection());
}

void JumpingState::Update(dae::GameObject* player, float deltaTime) {
    QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
    if (!qbertPlayer) return;

    m_JumpProgress += deltaTime / qbertPlayer->GetJumpDuration();

    const float t = m_JumpProgress < 0.5f ?
        4 * m_JumpProgress * m_JumpProgress * m_JumpProgress :
        1 - powf(-2 * m_JumpProgress + 2, 3) / 2;

    const float yOffset = sinf(t * std::numbers::pi_v<float>) * qbertPlayer->GetJumpHeight();
    const glm::vec3 newPos = glm::mix(
        m_JumpStartPos,
        qbertPlayer->GetJumpTargetPos(),
        t
    );
    qbertPlayer->SetPosition({ newPos.x, newPos.y - yOffset, newPos.z });

    if (m_JumpProgress >= 1.f) {
        qbertPlayer->ChangeState(std::make_unique<IdleState>());
    }
}

void JumpingState::Exit(dae::GameObject* player) {
    player->GetComponent<QBertPlayer>()->CompleteJump();
}
