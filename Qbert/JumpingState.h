#pragma once
#include <vec3.hpp>

#include "QBertState.h"

class JumpingState : public QBertState
{
public:
    void Enter(QBertPlayer* player) override;

    void Update(QBertPlayer* player, float deltaTime) override;

    void HandleInput(QBertPlayer*, const glm::ivec2&) override {}

    void Exit(QBertPlayer* player) override;

    std::string GetName() const override { return "Jumping"; }

private:
    float m_JumpProgress{ 0.f };
    glm::vec3 m_JumpStartPos{};
};
