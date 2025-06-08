#pragma once
#include <memory>
class Coily;
class CoilyState {
public:
    virtual ~CoilyState() = default;
    virtual  std::unique_ptr<CoilyState> Update(Coily* /*coily*/, float /*deltaTime*/) = 0;
};