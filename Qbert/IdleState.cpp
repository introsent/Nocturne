#include "IdleState.h"
#include "QBertPlayer.h"

#include "AnimationComponent.h"
#include "JumpingState.h"
#include "Tile.h"
#include "utils.h"
#include "Level.h"
#include "DeadState.h"

void IdleState::Enter(dae::GameObject* player) {
	QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
    if (!qbertPlayer) return;

    qbertPlayer->UpdateSpriteDirection(qbertPlayer->GetCurrentDirection());
}

void IdleState::HandleInput(dae::GameObject* player, const glm::ivec2& direction) {
    QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
    if (!qbertPlayer || direction == glm::ivec2(0)) return;

    Level* level = qbertPlayer->GetLevel();
    const glm::ivec2 newPos = qbertPlayer->GetCurrentGridPos() + direction;

    if (Tile* targetTile = level->GetTileAt(newPos)) {
        qbertPlayer->SetCurrentDirection(direction);
        qbertPlayer->SetCurrentGridPos(newPos);
        qbertPlayer->SetJumpTargetPos(glm::vec3(GridToWorldCharacter(newPos), 0.f));
        qbertPlayer->ChangeState(std::make_unique<JumpingState>());
    }
}

void IdleState::Update(dae::GameObject* player, float) {
    QBertPlayer* qbert = player->GetComponent<QBertPlayer>();
    if (!qbert) return;

    // 2. State-managed transition
    if (ShouldDie(qbert)) {
        qbert->ChangeState(std::make_unique<DeadState>());
    }
}

bool IdleState::ShouldDie(QBertPlayer* qbert) const {
    return qbert->GetLevel()->GetTileAt(qbert->GetCurrentGridPos())->GetType() == TileType::DEATH;
}
