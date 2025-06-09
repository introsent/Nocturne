#pragma once
#include "GridBasedMovement.h"
#include <numbers>

class JumpMovement : public GridBasedMovement {
public:
    JumpMovement(PositionConverter converter,
        float duration = 0.5f,
        float height = 32.f);

    void Start(const glm::ivec2& startGrid,
        const glm::ivec2& targetGrid);

    // Implement IMovementBehavior
    void Start(const glm::vec3& startWorld,
               const glm::vec3& targetWorld) override;
    bool Update(float deltaTime) override;
    glm::vec3 GetCurrentPosition() const override;
    void Reset() override;
    void SetParameters(float duration, float height);

    const glm::ivec2& GetTargetGrid() const { return m_targetGrid; }

private:
    glm::vec3 m_startWorld  {};
    glm::vec3 m_targetWorld {};
    float m_progress = 0.f;
    float m_duration;
    float m_height;
    bool m_isMoving = false;
};