#include "PlayerDataComponent.h"
#include "SceneManager.h"
#include "Scene.h"

PlayerDataComponent::PlayerDataComponent(dae::GameObject* owner)
    : Component(owner)
{
    auto scoreObj = std::make_unique<dae::GameObject>();
    m_pScore = scoreObj->AddComponent<ScoreComponent>(scoreObj.get());
    scoreObj->SetParent(GetOwner());
    dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(scoreObj));

    auto healthObj = std::make_unique<dae::GameObject>();
    m_pHealth = healthObj->AddComponent<HealthComponent>(healthObj.get());
    healthObj->SetParent(GetOwner());
    dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(healthObj));
}