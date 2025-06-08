#pragma once
#include <memory>
#include "CoilyState.h"
class SnakeState : public CoilyState {
public:
	virtual std::unique_ptr<CoilyState> Update(Coily* /*coily*/, float /*deltaTime*/) override { return nullptr; };
};