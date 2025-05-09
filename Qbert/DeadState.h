#pragma once
#include "QBertState.h"

class DeadState : public QBertState {
public:
    void Enter(QBertPlayer* player) override;

    void Update(QBertPlayer* player, float deltaTime) override;

    void HandleInput(QBertPlayer*, const glm::ivec2&) override {} // No input
    void Exit(QBertPlayer*) override {}

    std::string GetName() const override { return "Dead"; }

private:
    const float DEATH_DURATION = 2.f;
    float m_DeathTimer{ 0.f };
};


