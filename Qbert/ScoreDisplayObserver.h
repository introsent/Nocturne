#pragma once
#include "TextComponent.h"


class ScoreComponent;

class ScoreDisplayObserver final : public dae::Component
{
public:
	ScoreDisplayObserver(dae::GameObject* pOwner, dae::TextComponent* textComp);

	void Register(ScoreComponent* scoreComp);
	void Unregister(ScoreComponent* scoreComp);
private:
	dae::TextComponent* m_textComponent;
	int m_subscriptionToken = -1;
};



