#pragma once
#include <vec3.hpp>
#include "QBertState.h"

class JumpingState : public QBertState
{
public:
    JumpingState(dae::GameObject* owner, glm::ivec2 targetPosition)
		: QBertState(owner), m_targetGridPosition(targetPosition) {}
    void Enter(QBertPlayer* player) override;
    std::unique_ptr<QBertState> Update(QBertPlayer* player, float deltaTime) override;
    std::unique_ptr<QBertState> HandleInput(QBertPlayer*, const glm::ivec2&) override { return nullptr; }
    void Exit(QBertPlayer*) override {}
    bool CanAcceptInput() const override { return false;  }
    std::string GetName() const override { return "Jumping"; }

private:
    struct JumpData
    {
        float duration = 0.5f;
        float height = 32.f;
    };
    
    // Position data
    const glm::ivec2 m_targetGridPosition;
    glm::vec3 m_startWorldPosition{};
    glm::vec3 m_targetWorldPosition{};

    float m_jumpProgress{ 0.f };

    JumpData m_jumpData{ };
};
