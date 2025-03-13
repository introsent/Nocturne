#include "ScoreCommand.h"

#include "ScoreComponent.h"

dae::ScoreCommand::ScoreCommand(GameObject* pObject, int scoreAmount) : m_pObject(pObject), m_scoreAmount(scoreAmount)
{

}

void dae::ScoreCommand::Execute()
{
    if (m_pObject) {
        if (auto score = m_pObject->GetComponent<ScoreComponent>()) {
            score->AddScore(m_scoreAmount);
        }
    }
}
