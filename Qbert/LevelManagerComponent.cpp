#include "LevelManagerComponent.h"
#include "LevelComponent.h"
#include "SceneManager.h"
#include "Scene.h"

LevelManagerComponent::LevelManagerComponent(dae::GameObject* owner, PlayerDataComponent* playerData, GameMode mode)
    : Component(owner), m_pPlayerData(playerData), m_Mode(mode)
{
    LoadNextLevel();
}

void LevelManagerComponent::Update(float)
{
    if (m_LevelCompletedFlag)
    {
        m_LevelCompletedFlag = false;
        HandleLevelCompleted();
    }
}

void LevelManagerComponent::SetPlayerData(PlayerDataComponent* playerData)
{
    m_pPlayerData = playerData;
}

void LevelManagerComponent::SkipLevel()
{
    m_LevelCompletedFlag = true;
}

void LevelManagerComponent::LoadNextLevel()
{
    GetOwner()->DestroyChildren();

    auto levelController = std::make_unique<dae::GameObject>();
    auto levelComp = levelController->AddComponent<LevelComponent>(
        levelController.get(),
        m_CurrentLevelIndex,
        m_CurrentStageIndex,
        m_pPlayerData,
        m_Mode
    );

    levelComp->OnLevelCompletedEvent.Subscribe([this]() {
        m_LevelCompletedFlag = true;
        });

    levelController->SetParent(GetOwner());
    dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(levelController));
}

void LevelManagerComponent::HandleLevelCompleted()
{
    m_CurrentStageIndex++;

    constexpr int MAX_STAGES = 4;
    if (m_CurrentStageIndex > MAX_STAGES)
    {
        m_CurrentStageIndex = 1;
        m_CurrentLevelIndex++;

        const int MAX_LEVELS = 3;
        if (m_CurrentLevelIndex > MAX_LEVELS)
        {
            OnAllLevelsCompleted.Invoke();
            return;
        }
    }
    LoadNextLevel();
}