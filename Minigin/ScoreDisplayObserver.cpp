#include "ScoreDisplayObserver.h"

#include <iostream>

#include "ScoreComponent.h"

namespace dae
{
	ScoreDisplayObserver::ScoreDisplayObserver(GameObject* pOwner, TextComponent* textComp) : Component(pOwner), m_textComponent(textComp) {
	}

	void ScoreDisplayObserver::Notify(Event event, Subject* subject)
	{
		if (event == Event::PlayerDied)
		{
			if (auto player = dynamic_cast<ScoreComponent*>(subject)) {
				int playerScore = player->GetScore();
				if (m_textComponent)
					m_textComponent->SetText("Score: " + std::to_string(playerScore));
			}
			else {
				std::cerr << "Error: Subject is not a PlayerComponent!" << std::endl;
			}
		}
	}

	void ScoreDisplayObserver::Register(ScoreComponent* scoreComp)
	{
		scoreComp->AddObserver(this);
	}

	void ScoreDisplayObserver::Unregister(ScoreComponent* scoreComp)
	{
		scoreComp->RemoveObserver(this);
	}


}

