#pragma once
#include "ScoreComponent.h"

namespace dae
{
	class AchievementObserver : public Component
	{
	public:
		AchievementObserver(GameObject* pOwner) : Component(pOwner) {}

		void Register(ScoreComponent* scoreComp);
		void Unregister(ScoreComponent* scoreComp);

	private:
		int m_subscriptionToken = -1;
	};
}


