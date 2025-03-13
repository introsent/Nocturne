#include "AchievementsGlobals.h"

#include <array>

#include "Achievements.h"

// Define g_Achievements in only one .cpp file
std::array<Achievement_t, 1> g_Achievements = {
    _ACH_ID(static_cast<int>(EAchievements::ACH_WIN_ONE_GAME), "Winner")
};