#include "IdleState.h"
#include "QBertPlayer.h"
#include <iostream>

#include "AnimationComponent.h"
#include "JumpingState.h"

void IdleState::Enter(QBertPlayer* player) {
    player->UpdateSpriteDirection(player->GetCurrentDirection());
}

void IdleState::HandleInput(QBertPlayer* player, const glm::ivec2& direction) {
    if (player->TryStartJump(direction)) {
        player->ChangeState(std::make_unique<JumpingState>());
    }
}
