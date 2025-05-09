#include "JumpingState.h"
#include <numbers>
#include "QBertPlayer.h"

#include "IdleState.h"

void JumpingState::Enter(QBertPlayer* player) {
    m_JumpProgress = 0.f;
    m_JumpStartPos = player->GetCurrentPosition();
    player->UpdateSpriteDirection(player->GetCurrentDirection());
}

void JumpingState::Update(QBertPlayer* player, float deltaTime) {
    m_JumpProgress += deltaTime / player->GetJumpDuration();

    const float t = m_JumpProgress < 0.5f ?
        4 * m_JumpProgress * m_JumpProgress * m_JumpProgress :
        1 - powf(-2 * m_JumpProgress + 2, 3) / 2;

    const float yOffset = sinf(t * std::numbers::pi_v<float>) * player->GetJumpHeight();
    const glm::vec3 newPos = glm::mix(
        m_JumpStartPos,
        player->GetJumpTargetPos(),
        t
    );
    player->SetPosition({ newPos.x, newPos.y - yOffset, newPos.z });

    if (m_JumpProgress >= 1.f) {
        player->ChangeState(std::make_unique<IdleState>());
    }
}

void JumpingState::Exit(QBertPlayer* player) {
    player->CompleteJump();
}
