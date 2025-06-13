#pragma once
#include "Enemy.h"
#include "JumpMovement.h"

class SimpleEnemy : public Enemy {
public:
    SimpleEnemy(dae::GameObject* owner, Level* level, glm::ivec2 spawnGridPosition,
        const MultiQbertPositionProxy& qbertPositionProxy, PositionConverter converter);

    void Update(float deltaTime) override;

protected:
    virtual void GenerateNextMove() = 0;
    virtual void OnLand() = 0;

    void StartDying(bool byQbert);

    JumpMovement m_jumpMovement;
    glm::ivec2 m_targetGridPos{};

    bool m_isDying = false;
    bool m_isWaiting = true;
    bool m_isJumping = false;
    float m_delayTimer = 0.0f;
    const float JUMP_DELAY = 0.2f;
};