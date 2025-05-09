#include "JumpingState.h"
#include <numbers>
#include "QBertPlayer.h"

#include "IdleState.h"

void JumpingState::Enter(dae::GameObject* player) {
    m_JumpProgress = 0.f;
    m_JumpStartPos = player->GetComponent<QBertPlayer>()->GetCurrentPosition();
    player->GetComponent<QBertPlayer>()->UpdateSpriteDirection(player->GetComponent<QBertPlayer>()->GetCurrentDirection());
}

void JumpingState::Update(dae::GameObject* player, float deltaTime) {
    m_JumpProgress += deltaTime / player->GetComponent<QBertPlayer>()->GetJumpDuration();

    const float t = m_JumpProgress < 0.5f ?
        4 * m_JumpProgress * m_JumpProgress * m_JumpProgress :
        1 - powf(-2 * m_JumpProgress + 2, 3) / 2;

    const float yOffset = sinf(t * std::numbers::pi_v<float>) * player->GetComponent<QBertPlayer>()->GetJumpHeight();
    const glm::vec3 newPos = glm::mix(
        m_JumpStartPos,
        player->GetComponent<QBertPlayer>()->GetJumpTargetPos(),
        t
    );
    player->GetComponent<QBertPlayer>()->SetPosition({ newPos.x, newPos.y - yOffset, newPos.z });

    if (m_JumpProgress >= 1.f) {
        player->GetComponent<QBertPlayer>()->ChangeState(std::make_unique<IdleState>());
    }
}

void JumpingState::Exit(dae::GameObject* player) {
    player->GetComponent<QBertPlayer>()->CompleteJump();
}
