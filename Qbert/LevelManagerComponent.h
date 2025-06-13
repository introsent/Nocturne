#pragma once
#include "Component.h"
#include "Event.h"
#include "PlayerDataComponent.h"
#include "GameMode.h"

class LevelManagerComponent final : public dae::Component
{
public:
    LevelManagerComponent(dae::GameObject* owner, PlayerDataComponent* playerData, GameMode mode);
    void Update(float deltaTime) override;

    Event<> OnAllLevelsCompleted; 

    void SetPlayerData(PlayerDataComponent* playerData);
    PlayerDataComponent* GetPlayerData() const { return m_pPlayerData; }

private:
    void LoadNextLevel();
    void HandleLevelCompleted();

    int m_CurrentLevelIndex{ 1 };
    int m_CurrentStageIndex{ 1 };
    bool m_LevelCompletedFlag{ false };

    PlayerDataComponent* m_pPlayerData;

    GameMode m_Mode;
};