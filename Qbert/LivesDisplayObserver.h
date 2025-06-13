#pragma once
#include "TextComponent.h"


class HealthComponent;

class LivesDisplayObserver final : public dae::Component
{
public:
	LivesDisplayObserver(dae::GameObject* pOwner, dae::TextComponent* textComp);

	void Register(HealthComponent* healthComp);
	void Unregister(HealthComponent* healthComp);
private:
	int m_subscriptionToken = -1;
	dae::TextComponent* m_textComponent;
};



