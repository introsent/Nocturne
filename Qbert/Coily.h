#pragma once
#include "Enemy.h"
#include "EggState.h"
#include "CoilyState.h"
#include "SnakeState.h"
#include "AnimationComponent.h"
class Coily : public Enemy {
public:
	Coily(dae::GameObject* owner, Level* level)
		: Enemy(owner, level) {
		m_pAnimation = owner->GetComponent<AnimationComponent>();
	}

    void Update(float deltaTime) override {
        if (state) state->Update(this, deltaTime);
    }

    void TransformToSnake() {
        state = std::make_unique<SnakeState>();
    }

private:
    std::unique_ptr<CoilyState> state = std::make_unique<EggState>();
    AnimationComponent* m_pAnimation = nullptr;
};