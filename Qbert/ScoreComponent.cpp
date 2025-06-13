#include "ScoreComponent.h"

void ScoreComponent::AddScore(int amount)
{
	m_score += amount;
	OnScoreChanged(m_score);
}

int ScoreComponent::GetScore() const
{
	return m_score;
}
