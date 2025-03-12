#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class HealthComponent;

	class LivesDisplayObserver : Observer
	{
	public:
		LivesDisplayObserver(std::shared_ptr<GameObject> textObject, int maxLives);
		void Notify(Event event, Subject* subject) override;

		void Register(HealthComponent* healthComponent);
	private:
		std::shared_ptr<GameObject> m_textObject;
		TextComponent* m_textComponent;
		int m_remainingLives;

	
	};
}


