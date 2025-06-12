#include "LevelManagerComponent.h"
#include "LevelComponent.h"
#include "SceneManager.h"
#include "Scene.h"

LevelManagerComponent::LevelManagerComponent(dae::GameObject* owner)
    : Component(owner)
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

void LevelManagerComponent::LoadNextLevel()
{
   // GetOwner()->GetComponent<LevelComponent>()->
    // Destroy existing level children
    GetOwner()->DestroyChildren();

    // Create new level
    auto levelController = std::make_unique<dae::GameObject>();
    auto levelComp = levelController->AddComponent<LevelComponent>(
        levelController.get(),
        m_CurrentLevelIndex,
        m_CurrentStageIndex
    );

    // Subscribe to level completion
    levelComp->OnLevelCompletedEvent.Subscribe([this]() {
        m_LevelCompletedFlag = true;
        });

    levelController->SetParent(GetOwner());
  
    dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(levelController));
}

void LevelManagerComponent::HandleLevelCompleted()
{
    // Advance to next stage/level
    m_CurrentStageIndex++;

    constexpr int MAX_STAGES = 4;  // 4 stages per level
    if (m_CurrentStageIndex > MAX_STAGES)
    {
        m_CurrentStageIndex = 1;
        m_CurrentLevelIndex++;

        const int MAX_LEVELS = 3;  //: 3 levels total
        if (m_CurrentLevelIndex > MAX_LEVELS)
        {
            OnAllLevelsCompleted.Invoke();
            return;
        }
    }
    LoadNextLevel();
}