#include "ScoreDisplayObserver.h"

#include <iostream>

#include "ScoreComponent.h"


ScoreDisplayObserver::ScoreDisplayObserver(dae::GameObject* pOwner, dae::TextComponent* textComp) : Component(pOwner), m_textComponent(textComp) {
}
 

void ScoreDisplayObserver::Register(ScoreComponent* scoreComp)
{
	m_subscriptionToken = scoreComp->OnScoreChanged.Subscribe(
		[this, scoreComp](int newScore) {
			if (m_textComponent)
				m_textComponent->SetText("Score: " + std::to_string(newScore));
		}
	);
}

void ScoreDisplayObserver::Unregister(ScoreComponent* scoreComp)
{
	if (m_subscriptionToken != -1)
	{
		scoreComp->OnScoreChanged.Unsubscribe(m_subscriptionToken);
		m_subscriptionToken = -1;
	}
}



