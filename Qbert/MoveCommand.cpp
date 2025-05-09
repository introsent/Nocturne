#include "MoveCommand.h"
#include "QBertPlayer.h"

MoveCommand::MoveCommand(dae::GameObject* pObject, const glm::ivec2& direction) : m_pPlayer(pObject), m_Direction(direction)
{
}

void MoveCommand::Execute() {
    if (m_pPlayer && m_pPlayer->GetComponent<QBertPlayer>()->CanAcceptInput()) {
        m_pPlayer->GetComponent<QBertPlayer>()->GetState()->HandleInput(m_pPlayer, m_Direction);
    }
}

