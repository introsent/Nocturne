#include "LivesDisplayObserver.h"

#include "HealthComponent.h"

namespace dae
{
	LivesDisplayObserver::LivesDisplayObserver(std::shared_ptr<GameObject> textObject, int maxLives)
		: m_textObject(textObject), m_remainingLives(maxLives) {
		m_textComponent = m_textObject->AddComponent<TextComponent>(m_textObject.get(), "Remaining Lives: " + std::to_string(m_remainingLives));
	}

	void LivesDisplayObserver::Notify(Event event, Subject* subject)
	{
		if (event == Event::PlayerDied)
		{
			--m_remainingLives;
			if (m_textComponent) {
				m_textComponent->SetText("Remaining Lives: " + std::to_string(m_remainingLives));
			}
		}
	}
	void LivesDisplayObserver::Register(HealthComponent* healthComponent)
	{
		healthComponent->AddObserver(this);
	}
}

