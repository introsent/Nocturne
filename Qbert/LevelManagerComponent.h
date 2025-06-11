#pragma once
#include "Component.h"
#include "Event.h"

class LevelManagerComponent final : public dae::Component
{
public:
    LevelManagerComponent(dae::GameObject* owner);
    void Update(float deltaTime) override;

    Event<> OnAllLevelsCompleted; 

private:
    void LoadNextLevel();
    void HandleLevelCompleted();

    int m_CurrentLevelIndex{ 1 };
    int m_CurrentStageIndex{ 1 };
    bool m_LevelCompletedFlag{ false };
};