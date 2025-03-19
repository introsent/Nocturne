#include "AchievementObserver.h"

#include <iostream>

#include "AchievementsGlobals.h"
#include "CSteamAchievements.h"

void dae::AchievementObserver::Register(ScoreComponent* scoreComp)
{
    m_subscriptionToken = scoreComp->OnScoreChanged.Subscribe(
        [this, scoreComp](int newScore) {
            if (newScore >= 500)
            {
                if (g_SteamAchievements)
                {
                    g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
                    // unsubscribe after unlocking the achievement.
                    Unregister(scoreComp);
                }
            }
        }
    );
}

void dae::AchievementObserver::Unregister(ScoreComponent* scoreComp)
{
    if (m_subscriptionToken != -1)
    {
        scoreComp->OnScoreChanged.Unsubscribe(m_subscriptionToken);
        m_subscriptionToken = -1;
    }
}
