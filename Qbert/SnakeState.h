#pragma once
#include <memory>
#include "CoilyState.h"
#include "utils.h"
#include "JumpMovement.h"

class SnakeState : public CoilyState {
public:
	SnakeState(dae::GameObject* owner)
		: CoilyState(owner),
		m_jump([this](const glm::ivec2& grid) { return GridToWorldCoily(grid); })
	{}
	virtual std::unique_ptr<CoilyState> Update(Coily* /*coily*/, float /*deltaTime*/) override { return nullptr; };
	void Enter(Coily*) override {}
	void Exit(Coily*) override {}
	std::string GetName() const override { return "Snake"; }
private:
	glm::ivec2 m_targetGridPosition{};
	JumpMovement m_jump;
};