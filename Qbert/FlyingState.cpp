#include "FlyingState.h"
#include "Level.h"
#include "QBertPlayer.h"
#include "LevelComponent.h"
#include "utils.h"
#include "AnimationComponent.h"
#include <TranslationComponent.h>
#include "IdleState.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DiscManager.h"

void FlyingState::Enter(dae::GameObject* player)
{
    // 1) grab Q*bert data
    QBertPlayer* q = player->GetComponent<QBertPlayer>();
    auto gridPos = q->GetCurrentGridPos();

    m_pDiscGO = DiscManager::GetInstance().GetDiscAt(gridPos);

    // 3) record start positions
    m_QBertStart = player->GetWorldPosition();
    m_DiscStart = m_pDiscGO->GetWorldPosition();

    // 4) compute target world pos
    glm::ivec2 topGrid{ 0,0 };
    glm::vec2 topWorld = GridToWorldCharacter(topGrid);
    m_TargetPos = glm::vec3(topWorld.x, topWorld.y, 0.f);

    // 6) kick off disc animation (if not already)
    if (auto anim = m_pDiscGO->GetComponent<AnimationComponent>()) {
        anim->SetAutoAdvance(true);
    }

    m_FlyTimer = 0.f;
}

void FlyingState::Update(dae::GameObject* player, float deltaTime) {
    m_FlyTimer += deltaTime;
    float t = glm::clamp(m_FlyTimer / m_FlyDuration, 0.f, 1.f);

    // Interpolate positions
    glm::vec3 qpos = glm::mix(m_QBertStart, m_TargetPos, t);
    glm::vec3 dpos = glm::mix(m_DiscStart, m_TargetPos, t);

    // Set positions directly (not via Translate)
    player->SetLocalPosition(qpos);
    m_pDiscGO->SetLocalPosition(dpos);

    if (t >= 1.0f) {
        dae::SceneManager::GetInstance().GetActiveScene()->Remove(m_pDiscGO);

        // Ensure QBert snaps to the exact target position
        player->SetLocalPosition(m_TargetPos);

        m_pDiscGO.reset();
        auto q = player->GetComponent<QBertPlayer>();
        q->ChangeState(std::make_unique<IdleState>());
    }
}
