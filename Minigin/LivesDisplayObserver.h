#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class HealthComponent;

	class LivesDisplayObserver final : public Observer, public Component
	{
	public:
		LivesDisplayObserver(GameObject* pOwner, TextComponent* textComp);

		void Notify(Event event, Subject* subject) override;

		void Register(HealthComponent* healthComp);
		void Unregister(HealthComponent* healthComp);
	private:
		TextComponent* m_textComponent;
	};
}


