#include "ScoreComponent.h"

#include "Achievements.h"
#include "AchievementsGlobals.h"
#include "CSteamAchievements.h"

void dae::ScoreComponent::AddScore(int amount)
{
	m_score += amount;
	NotifyObservers(Event::PlayerScored, this);
}

int dae::ScoreComponent::GetScore() const
{
	return m_score;
}
