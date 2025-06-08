#pragma once
#include <vec3.hpp>
#include "QBertState.h"
#include "JumpMovement.h"
#include "utils.h"

class JumpingState : public QBertState
{
public:
    JumpingState(dae::GameObject* owner, glm::ivec2 targetPosition)
		: QBertState(owner), m_targetGridPosition(targetPosition),
        m_jump([this](const glm::ivec2& grid) { return GridToWorldCharacter(grid);})
    {}
    void Enter(QBertPlayer* player) override;
    std::unique_ptr<QBertState> Update(QBertPlayer* player, float deltaTime) override;
    std::unique_ptr<QBertState> HandleInput(QBertPlayer*, const glm::ivec2&) override { return nullptr; }
    void Exit(QBertPlayer*) override {}
    bool CanAcceptInput() const override { return false;  }
    std::string GetName() const override { return "Jumping"; }

private:
    glm::ivec2 m_targetGridPosition;
    JumpMovement m_jump;
};
