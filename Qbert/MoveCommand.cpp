#include "MoveCommand.h"
#include "QBertPlayer.h"
#include "Coily.h"

MoveCommand::MoveCommand(dae::GameObject* pObject, const glm::ivec2& direction) : m_pPlayer(pObject), m_Direction(direction)
{
}

void MoveCommand::Execute() {
    if (!m_pPlayer) return;
	if (m_pPlayer->IsMarkedForDestroy()) return;


    QBertPlayer* player = m_pPlayer->GetComponent<QBertPlayer>();
    if (player && player->IsAcceptingInput()) {
        player->HandleInput(m_Direction);
    }

	Coily* coily = m_pPlayer->GetComponent<Coily>();
    if (coily && coily->IsPlayerControlled())
    {
		coily->HandleInput(m_Direction);
    }
}

