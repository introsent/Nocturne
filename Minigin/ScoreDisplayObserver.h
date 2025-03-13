#pragma once
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{
	class ScoreComponent;

	class ScoreDisplayObserver final : public Observer, public Component
	{
	public:
		ScoreDisplayObserver(GameObject* pOwner, TextComponent* textComp);

		void Notify(Event event, Subject* subject) override;

		void Register(ScoreComponent* scoreComp);
		void Unregister(ScoreComponent* scoreComp);
	private:
		TextComponent* m_textComponent;
	};
}


