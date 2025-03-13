#include "AchievementsGlobals.h"
#include "CSteamAchievement.h"

// Define your achievement IDs (must match your Steam configuration)
enum EAchievements
{
    ACH_WIN_ONE_GAME = 0,
};

Achievement_t g_Achievements[] =
{
    _ACH_ID(ACH_WIN_ONE_GAME, "Winner")
};

CSteamAchievements* g_SteamAchievements = nullptr;
