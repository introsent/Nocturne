#include "ScoreComponent.h"

void dae::ScoreComponent::AddScore(int amount)
{
	m_score += amount;
	OnScoreChanged(m_score);
}

int dae::ScoreComponent::GetScore() const
{
	return m_score;
}
