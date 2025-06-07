#pragma once
#include <memory>
#include <string>
#include "GameObject.h"

class QBertPlayer;

class QBertState {
public:
	explicit QBertState(dae::GameObject* owner) : owner(owner) {}
    virtual ~QBertState() = default;
    virtual void Enter(QBertPlayer* player) = 0;
    virtual std::unique_ptr<QBertState> Update(QBertPlayer* player, float deltaTime) = 0;
    virtual std::unique_ptr<QBertState> HandleInput(QBertPlayer* player, const glm::ivec2& direction) = 0;
    virtual bool CanAcceptInput() const = 0;
    virtual void Exit(QBertPlayer* player) = 0;
    virtual std::string GetName() const = 0;

protected:
    dae::GameObject* owner = nullptr;
};
