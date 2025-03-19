#pragma once
#include "TextComponent.h"

namespace dae
{
	class HealthComponent;

	class LivesDisplayObserver final : public Component
	{
	public:
		LivesDisplayObserver(GameObject* pOwner, TextComponent* textComp);

		void Register(HealthComponent* healthComp);
		void Unregister(HealthComponent* healthComp);
	private:
		int m_subscriptionToken = -1;
		TextComponent* m_textComponent;
	};
}


