#pragma once
#include "Observer.h"
#include "ScoreComponent.h"

namespace dae
{
	class AchievementObserver : public Observer, public Component
	{
	public:
		AchievementObserver(GameObject* pOwner) : Component(pOwner) {}

		void Notify(Event event, Subject* subject) override;

		void Register(ScoreComponent* scoreComp);
		void Unregister(ScoreComponent* scoreComp);
	};
}


