#pragma once
#include <string>
#include <vec2.hpp>

class QBertPlayer;

class QBertState {
public:
    virtual ~QBertState() = default;
    virtual void Enter(QBertPlayer* player) = 0;
    virtual void Update(QBertPlayer* player, float deltaTime) = 0;
    virtual void HandleInput(QBertPlayer* player, const glm::ivec2& direction) = 0;
    virtual void Exit(QBertPlayer* player) = 0;
    virtual std::string GetName() const = 0;
};
