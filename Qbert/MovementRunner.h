#pragma once
#include <functional>
#include <memory>
#include "IMovementBehaviour.h"
#include <GameObject.h>
#include <Component.h>

class MovementRunner : public dae::Component {
public:
    MovementRunner(std::unique_ptr<IMovementBehaviour> movement,
        std::function<void()> onComplete, dae::GameObject* owner)
        : dae::Component(owner), m_movement(std::move(movement)), m_onComplete(onComplete) {
    }

    void Update(float deltaTime) override {
        if (m_movement->Update(deltaTime)) {
            if (m_onComplete) m_onComplete();
            GetOwner()->RemoveComponent(this);
        }
        GetOwner()->SetLocalPosition(m_movement->GetCurrentPosition());
    }

private:
    std::unique_ptr<IMovementBehaviour> m_movement;
    std::function<void()> m_onComplete;
};