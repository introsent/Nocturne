#pragma once
#include "QBertState.h"

class FlyingState : public QBertState
{
    void Enter(dae::GameObject* player) override;

    void Update(dae::GameObject* player, float deltaTime) override;

    void HandleInput(dae::GameObject*, const glm::ivec2&) override {}

    void Exit(dae::GameObject*) override {}

    bool CanAcceptInput() const override { return false; }

    std::string GetName() const override { return "Dead"; }

private:
    float                   m_FlyTimer{};
    float                   m_FlyDuration{ 2.f };
    glm::vec3               m_QBertStart;
    glm::vec3               m_DiscStart;
    glm::vec3               m_TargetPos;      // world pos of top cell
    std::shared_ptr<dae::GameObject> m_pDiscGO;
};

