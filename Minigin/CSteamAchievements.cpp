#include "CSteamAchievements.h"
#include <steam_api.h>
#include <cstdio>
#include <SDL_syswm.h>

CSteamAchievements::CSteamAchievements(Achievement_t* pAchievements, int numAchievements)
    : m_iAppID(0)
    , m_pAchievements(pAchievements)
    , m_iNumAchievements(numAchievements)
    , m_bInitialized(false)
    , m_CallbackUserStatsReceived(this, &CSteamAchievements::OnUserStatsReceived)
    , m_CallbackUserStatsStored(this, &CSteamAchievements::OnUserStatsStored)
    , m_CallbackAchievementStored(this, &CSteamAchievements::OnAchievementStored)
{
    m_iAppID = SteamUtils()->GetAppID();
    RequestStats();
}

CSteamAchievements::~CSteamAchievements()
{
}

bool CSteamAchievements::RequestStats()
{
   
    if (SteamUserStats() == nullptr || SteamUser() == nullptr)
        return false;
    if (!SteamUser()->BLoggedOn())
        return false;

    return SteamUserStats()->RequestCurrentStats();
}

bool CSteamAchievements::SetAchievement(const char* id) const
{
    if (m_bInitialized)
    {
        SteamUserStats()->SetAchievement(id);
        return SteamUserStats()->StoreStats();
    }
    return false;
}

void CSteamAchievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
    if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
    {
        if (k_EResultOK == pCallback->m_eResult)
        {
            OutputDebugString("Received stats and achievements from Steam\n");
            m_bInitialized = true;

            for (int i = 0; i < m_iNumAchievements; ++i)
            {
                Achievement_t& ach = m_pAchievements[i];
                SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
                _snprintf_s(ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
                    SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID, "name"));
                _snprintf_s(ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
                    SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID, "desc"));
            }
        }
        else
        {
            char buffer[128];
            _snprintf_s(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
            OutputDebugString(buffer);
        }
    }
}

void CSteamAchievements::OnUserStatsStored(UserStatsStored_t* pCallback)
{
    if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
    {
        if (k_EResultOK == pCallback->m_eResult)
        {
            OutputDebugString("Stored stats for Steam\n");
        }
        else
        {
            char buffer[128];
            _snprintf_s(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult);
            OutputDebugString(buffer);
        }
    }
}

void CSteamAchievements::OnAchievementStored(UserAchievementStored_t* pCallback)
{
    if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
    {
        OutputDebugString("Stored Achievement for Steam\n");
    }
}

