#pragma once
#include <vec3.hpp>

#include "QBertState.h"

class JumpingState : public QBertState
{
public:
    void Enter(dae::GameObject* player) override;

    void Update(dae::GameObject* player, float deltaTime) override;

    void HandleInput(dae::GameObject*, const glm::ivec2&) override {}

    void Exit(dae::GameObject* player) override;

    std::string GetName() const override { return "Jumping"; }

private:
    float m_JumpProgress{ 0.f };
    glm::vec3 m_JumpStartPos{};
};
