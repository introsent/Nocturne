#pragma once
#include "QBertState.h"
class FlyingState : public QBertState
{
    void Enter(dae::GameObject* player) override;
    void Update(dae::GameObject* player, float deltaTime) override;
    void HandleInput(dae::GameObject*, const glm::ivec2&) override {}
    void Exit(dae::GameObject*) override {}
    bool CanAcceptInput() const override { return false; }
    std::string GetName() const override { return "Flying"; }
private:
    enum class FlyingPhase
    {
        Flying,
        Dropping,
        Complete
    };

    float                   m_flyTimer{};
    float                   m_flyDuration{ 2.f };
    float                   m_dropDuration{ 0.5f };
    FlyingPhase             m_currentPhase{ FlyingPhase::Flying };
    glm::vec3               m_qbertStartPos;
    glm::vec3               m_discStartPos;
    glm::vec3               m_targetWorldPos;      // world pos of top cell
    glm::vec3               m_actualTopPos;        // actual position of 0,0 grid
    std::shared_ptr<dae::GameObject> m_pDiscObject;
};

