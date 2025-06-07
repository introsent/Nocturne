#pragma once
#include "QBertState.h"

class IdleState : public QBertState
{
public:
	IdleState(dae::GameObject* owner)
		: QBertState(owner) {}
    void Enter(QBertPlayer* player) override;
    std::unique_ptr<QBertState> Update(QBertPlayer*, float) override;
    std::unique_ptr<QBertState> HandleInput(QBertPlayer* player, const glm::ivec2& direction) override;
    void Exit(QBertPlayer*) override {}
    bool CanAcceptInput() const override { return true; }
    std::string GetName() const override { return "Idle"; }

private:
    bool ShouldDie(QBertPlayer* qbert) const;
    bool ShouldFly(QBertPlayer* qbert) const;
};

