#pragma once
#include "Component.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"


class PlayerDataComponent : public dae::Component {
public:
    PlayerDataComponent(dae::GameObject* owner);

    ScoreComponent* GetScore() const { return m_pScore; }
    HealthComponent* GetHealth() const { return m_pHealth; }

    void SetNickname (const std::string& name) {
        m_nickname = name;
	}

	std::string GetNickname() const { return m_nickname; }

private:
    ScoreComponent* m_pScore;
    HealthComponent* m_pHealth;
    std::string m_nickname;
};
