#pragma once
#include "QBertState.h"

class IdleState : public QBertState
{
    void Enter(QBertPlayer* player) override;

    void Update(QBertPlayer*, float) override {}

    void HandleInput(QBertPlayer* player, const glm::ivec2& direction) override;

    void Exit(QBertPlayer*) override {}

    std::string GetName() const override { return "Idle"; }
};

