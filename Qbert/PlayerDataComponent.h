#pragma once
#include "Component.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"


class PlayerDataComponent : public dae::Component {
public:
    PlayerDataComponent(dae::GameObject* owner);

    ScoreComponent* GetScore() const { return m_pScore; }
    HealthComponent* GetHealth() const { return m_pHealth; }

private:
    ScoreComponent* m_pScore;
    HealthComponent* m_pHealth;
};
