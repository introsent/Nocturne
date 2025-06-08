#pragma once
#include "Enemy.h"
#include "EggState.h"
#include "CoilyState.h"
#include "SnakeState.h"
#include "AnimationComponent.h"
#include "QBertPlayer.h"

class Coily : public Enemy {
public:
	Coily(dae::GameObject* owner, Level* level, QBertPlayer* qbert)
		: Enemy(owner, level), m_pQBert(qbert) {
		m_pAnimation = owner->GetComponent<AnimationComponent>();
	}

    void Update(float deltaTime) override {
        if (state) {
            if (auto newState = state->Update(this, deltaTime)) {
                TransitionTo(std::move(newState));
            }
        }
    }

    void TransitionTo(std::unique_ptr<CoilyState> newState) {
        if (state) {
            state->Exit(this);
        }

        state = std::move(newState);

        if (state) {
            state->Enter(this);
        }
    }

    void UpdateAnimation(int frame);

	glm::ivec2 GetQBertGridPosition() const { return m_pQBert->GetGridPosition(); }
private:
    QBertPlayer* m_pQBert;
    std::unique_ptr<CoilyState> state = std::make_unique<EggState>(GetOwner());
    AnimationComponent* m_pAnimation = nullptr;
};