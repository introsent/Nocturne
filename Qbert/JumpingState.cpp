#include "JumpingState.h"
#include <numbers>
#include "QBertPlayer.h"
#include "Level.h"
#include "IdleState.h"
#include "utils.h"

void JumpingState::Enter(QBertPlayer* player) {

    m_jumpProgress = 0.f;

    // Cache positions
    m_startWorldPosition = glm::vec3(GridToWorldCharacter(player->GetGridPosition()), 0);
    m_targetWorldPosition = glm::vec3(GridToWorldCharacter(m_targetGridPosition), 0);
    player->UpdateAnimation();
}

std::unique_ptr<QBertState> JumpingState::Update(QBertPlayer* player, float deltaTime) {
    m_jumpProgress += deltaTime / m_jumpData.duration;
    const float t = std::clamp(m_jumpProgress, 0.0f, 1.0f);

    // Smooth jump curve calculation
    const float yOffset = sinf(t * std::numbers::pi_v<float>) * m_jumpData.height;
    const glm::vec3 newPos = glm::mix(
        m_startWorldPosition,
        m_targetWorldPosition,
        t
    );

    owner->SetLocalPosition({ newPos.x, newPos.y - yOffset, newPos.z });

    if (m_jumpProgress >= 1.0f) {
        owner->SetLocalPosition(m_targetWorldPosition);
		player->MoveTo(m_targetGridPosition); 
        player->GetLevel()->HandleJump(player->GetGridPosition());

        return std::make_unique<IdleState>(owner);
    }

    return nullptr;
}