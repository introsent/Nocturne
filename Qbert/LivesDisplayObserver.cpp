#include "LivesDisplayObserver.h"

#include "HealthComponent.h"


LivesDisplayObserver::LivesDisplayObserver(dae::GameObject* pOwner, dae::TextComponent* textComp) : Component(pOwner), m_textComponent(textComp) {
}

void LivesDisplayObserver::Register(HealthComponent* healthComp)
{
	m_subscriptionToken = healthComp->OnHealthChanged.Subscribe([this, healthComp]() {
		int lives = healthComp->GetLives();
		if (m_textComponent)
			m_textComponent->SetText("Remaining Lives: " + std::to_string(lives));
		});
}

void LivesDisplayObserver::Unregister(HealthComponent* healthComp)
{
	if (m_subscriptionToken != -1)
	{
		healthComp->OnHealthChanged.Unsubscribe(m_subscriptionToken);
		m_subscriptionToken = -1;
	}
}
