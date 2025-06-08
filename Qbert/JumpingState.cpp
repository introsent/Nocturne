#include "JumpingState.h"
#include <numbers>
#include "QBertPlayer.h"
#include "Level.h"
#include "IdleState.h"
#include "utils.h"

void JumpingState::Enter(QBertPlayer* player) 
{
    m_jump.StartJump(player->GetGridPosition(), m_targetGridPosition);
    player->UpdateAnimation();
}

std::unique_ptr<QBertState> JumpingState::Update(QBertPlayer* player, float deltaTime) {
    if (m_jump.Update(deltaTime))
    {
        player->MoveTo(m_jump.GetTargetGrid());
        player->GetLevel()->HandleJump(player->GetGridPosition());
        return std::make_unique<IdleState>(owner);
    }

    owner->SetLocalPosition(m_jump.GetCurrentPosition());
    return nullptr;
}