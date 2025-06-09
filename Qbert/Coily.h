#pragma once
#include "Enemy.h"
#include "EggState.h"
#include "CoilyState.h"
#include "SnakeState.h"
#include "SpawningState.h"
#include "AnimationComponent.h"
#include "QBertPlayer.h"

class Coily : public Enemy {
public:
    Coily(dae::GameObject* owner, glm::ivec2 spawnGridPosition, Level* level, QBertPlayer* qbert);

    void Update(float deltaTime) override;

    void UpdateAnimation(int frame);
    void TransitionTo(std::unique_ptr<CoilyState> newState);

	glm::ivec2 GetQBertGridPosition() const { return m_pQBert->GetGridPosition(); }
    glm::ivec2 GetDesiredSpawnGridPosition() const { return m_desiredSpawnGridPosition; }

private:
    QBertPlayer* m_pQBert;
	glm::ivec2 m_desiredSpawnGridPosition = { 0, 0 };
    std::unique_ptr<CoilyState> m_currentState = std::make_unique<SpawningState>(GetOwner());
    AnimationComponent* m_pAnimation = nullptr;
};