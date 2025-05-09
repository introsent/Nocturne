#include "IdleState.h"
#include "QBertPlayer.h"
#include <iostream>

#include "AnimationComponent.h"
#include "JumpingState.h"

void IdleState::Enter(dae::GameObject* player) {
	QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
    if (!qbertPlayer) return;

    qbertPlayer->UpdateSpriteDirection(qbertPlayer->GetCurrentDirection());
}

void IdleState::HandleInput(dae::GameObject* player, const glm::ivec2& direction) {
    QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
    if (!qbertPlayer) return;

    if (qbertPlayer->TryStartJump(direction)) {
        qbertPlayer->ChangeState(std::make_unique<JumpingState>());
    }
}
