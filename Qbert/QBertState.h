#pragma once
#include <string>
#include <vec2.hpp>

#include "GameObject.h"

class QBertPlayer;

class QBertState {
public:
    virtual ~QBertState() = default;
    virtual void Enter(dae::GameObject* player) = 0;
    virtual void Update(dae::GameObject* player, float deltaTime) = 0;
    virtual void HandleInput(dae::GameObject* player, const glm::ivec2& direction) = 0;
    virtual void Exit(dae::GameObject* player) = 0;
    virtual std::string GetName() const = 0;
};
