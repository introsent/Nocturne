#pragma once
#include "CoilyState.h"
class EggState : public CoilyState {
public:
    std::unique_ptr<CoilyState> Update(Coily* /*coily*/, float /*deltaTime*/) override { return nullptr; }
};