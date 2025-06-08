#pragma once
#include "CoilyState.h"
#include <vec3.hpp>
#include "JumpMovement.h"
#include <string>
#include "utils.h"

class EggState : public CoilyState {
public:
    EggState(dae::GameObject* owner) 
		: CoilyState(owner),
		m_jump([this](const glm::ivec2& grid) { return GridToWorldCoily(grid); }) 
    {}
    void Enter(Coily* coily) override;
    std::unique_ptr<CoilyState> Update(Coily* coily, float deltaTime) override;
    void Exit(Coily* coily) override;
    std::string GetName() const override { return "Egg"; }

    static constexpr float JUMP_DELAY = 0.2f;
private: 
    void GenerateTargetGridPosition(Coily* coily);
    glm::ivec2 m_targetGridPosition{};
    JumpMovement m_jump;

    bool m_isDelaying = false;
    float m_delayTimer = 0.0f;
};