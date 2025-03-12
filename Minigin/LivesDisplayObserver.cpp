#include "LivesDisplayObserver.h"

#include "HealthComponent.h"

namespace dae
{
	LivesDisplayObserver::LivesDisplayObserver(GameObject* pOwner, TextComponent* textComp) : Component(pOwner), m_textComponent(textComp) {
	}

	void LivesDisplayObserver::Notify(Event event, Subject* subject)
	{
		if (event == Event::PlayerDied)
		{
			if (auto player = dynamic_cast<HealthComponent*>(subject)) {
				int lives = player->GetLives();
				if (m_textComponent)
					m_textComponent->SetText("Remaining Lives: " + std::to_string(lives));
			}
			else {
				std::cerr << "Error: Subject is not a PlayerComponent!" << std::endl;
			}
		}
	}

	void LivesDisplayObserver::Register(HealthComponent* healthComp)
	{
		healthComp->AddObserver(this);
	}

	void LivesDisplayObserver::Unregister(HealthComponent* healthComp)
	{
		healthComp->RemoveObserver(this);
	}

	
}

