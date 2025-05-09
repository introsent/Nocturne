#pragma once
#include "QBertState.h"
#include "TextureComponent.h"

class DeadState : public QBertState {
public:
    void Enter(dae::GameObject* player) override;

    void Update(dae::GameObject* player, float deltaTime) override;

    void HandleInput(dae::GameObject*, const glm::ivec2&) override {}

    void Exit(dae::GameObject* player) override;

    std::string GetName() const override { return "Dead"; }

private:
    std::shared_ptr<dae::GameObject> m_DialogueCloud;
    const float DEATH_DURATION = 2.f;
    float m_DeathTimer{ 0.f };
};


