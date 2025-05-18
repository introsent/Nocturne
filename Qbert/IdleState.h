#pragma once
#include "QBertState.h"

class IdleState : public QBertState
{
    void Enter(dae::GameObject* player) override;

    void Update(dae::GameObject*, float) override;

    void HandleInput(dae::GameObject* player, const glm::ivec2& direction) override;

    bool ShouldDie(QBertPlayer* qbert) const;

    void Exit(dae::GameObject*) override {}

    bool CanAcceptInput() const override { return true; }

    std::string GetName() const override { return "Idle"; }
};

