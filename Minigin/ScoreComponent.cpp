#include "ScoreComponent.h"

void dae::ScoreComponent::AddScore(int amount)
{
	m_score += amount;
	NotifyObservers(Event::PlayerDied, this);
}

int dae::ScoreComponent::GetScore() const
{
	return m_score;
}
