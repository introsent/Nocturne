#pragma once
#include "Enemy.h"
#include "EggState.h"
#include "CoilyState.h"
#include "SnakeState.h"
#include "AnimationComponent.h"
#include "QBertPlayer.h"

class Coily : public Enemy {
public:
    Coily(dae::GameObject* owner, Level* level, QBertPlayer* qbert);

    void Update(float deltaTime) override;

    void UpdateAnimation(int frame);
    void TransitionTo(std::unique_ptr<CoilyState> newState);

	glm::ivec2 GetQBertGridPosition() const { return m_pQBert->GetGridPosition(); }
private:
    QBertPlayer* m_pQBert;
    std::unique_ptr<CoilyState> m_currentState = std::make_unique<EggState>(GetOwner());
    AnimationComponent* m_pAnimation = nullptr;
};