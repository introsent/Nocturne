#pragma once
#pragma once
#include <array>

#include "Achievements.h"

class CSteamAchievements;

enum EAchievements
{
    ACH_WIN_ONE_GAME = static_cast<uint8_t>(0)
};

extern std::array<Achievement_t, 1> g_Achievements;

inline CSteamAchievements* g_SteamAchievements = nullptr;
