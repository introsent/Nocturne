#pragma once
#include <memory>
#include "GameObject.h"
#include <string>

class Coily;
class CoilyState {
public:
    CoilyState(dae::GameObject* owner) : owner(owner) {}
    virtual ~CoilyState() = default;
    virtual void Enter(Coily* coily) = 0;
    virtual std::unique_ptr<CoilyState> Update(Coily* coily, float deltaTime) = 0;
    virtual void Exit(Coily* coily) = 0;
    virtual std::string GetName() const = 0;

protected:
	dae::GameObject* owner = nullptr;
};