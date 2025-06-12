#include "IdleState.h"
#include "QBertPlayer.h"
#include "AnimationComponent.h"
#include "JumpingState.h"
#include "Tile.h"
#include "utils.h"
#include "Level.h"
#include "DeadState.h"
#include "FlyingState.h"
#include <SoundServiceLocator.h>

void IdleState::Enter(QBertPlayer* player) {
    player->UpdateAnimation();
}

std::unique_ptr<QBertState> IdleState::HandleInput(QBertPlayer* player, const glm::ivec2& direction) {
    if (direction == glm::ivec2(0)) return nullptr;
     
    Level* level = player->GetLevel();
	if (!level) return nullptr; 

    const glm::ivec2 newPos = player->GetGridPosition() + direction;

    if (Tile* targetTile = level->GetTileAt(newPos)) {
		player->LookAt(direction);
        return std::make_unique<JumpingState>(owner, newPos);
    }

    return nullptr;
}

std::unique_ptr<QBertState> IdleState::Update(QBertPlayer* player, float) {
    if (ShouldDie(player)) {
        dae::SoundServiceLocator::GetService()->PlaySound("qbert_fall");
        return std::make_unique<DeadState>(owner);
    }
    if (ShouldFly(player)) {
        player->GetLevel()->GetTileAt(player->GetGridPosition())->SetType(TileType::DEATH);
        return std::make_unique<FlyingState>(owner);
    }
    return nullptr;
}

std::unique_ptr<QBertState> IdleState::ProcessHit()
{
    return std::make_unique<DeadState>(owner);
}

bool IdleState::ShouldDie(QBertPlayer* qbert) const {
    return qbert->GetLevel()->GetTileAt(qbert->GetGridPosition())->GetType() == TileType::DEATH;
}

bool IdleState::ShouldFly(QBertPlayer* qbert) const {
    return qbert->GetLevel()->GetTileAt(qbert->GetGridPosition())->GetType() == TileType::DISC;
}

