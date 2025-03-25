#pragma once
#include "TextComponent.h"

namespace dae
{
	class ScoreComponent;

	class ScoreDisplayObserver final : public Component
	{
	public:
		ScoreDisplayObserver(GameObject* pOwner, TextComponent* textComp);

		void Register(ScoreComponent* scoreComp);
		void Unregister(ScoreComponent* scoreComp);
	private:
		TextComponent* m_textComponent;
		int m_subscriptionToken = -1;
	};
}


