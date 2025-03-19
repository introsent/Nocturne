#include "AchievementObserver.h"

#include <iostream>

#include "AchievementsGlobals.h"
#include "CSteamAchievements.h"

void dae::AchievementObserver::Notify(Event event, Subject* subject)
{
	if (event == Event::PlayerScored)
	{
		if (auto player = dynamic_cast<ScoreComponent*>(subject)) {
			if (player->GetScore() >= 500)
			{
				if (g_SteamAchievements)
				{
					g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
					Unregister(player);
				}
			}
		}
		else {
			std::cerr << "Error: Subject is not a PlayerComponent!" << std::endl;
		}
	}
}

void dae::AchievementObserver::Register(ScoreComponent* scoreComp)
{
	scoreComp->AddObserver(this);
}

void dae::AchievementObserver::Unregister(ScoreComponent* scoreComp)
{
	scoreComp->RemoveObserver(this);
}
