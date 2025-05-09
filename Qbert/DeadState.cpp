#include "DeadState.h"
#include "QBertPlayer.h"
#include <iostream>

#include "AnimationComponent.h"
#include "IdleState.h"

// Dead State
void DeadState::Enter(QBertPlayer* player) {
    player->GetAnimation()->SetFrame(player->GetDeathFrame());
    m_DeathTimer = 0.f;
}

void DeadState::Update(QBertPlayer* player, float deltaTime) {
    m_DeathTimer += deltaTime;
    if (m_DeathTimer >= DEATH_DURATION) {
        player->Respawn();
        player->ChangeState(std::make_unique<IdleState>());
    }
}
