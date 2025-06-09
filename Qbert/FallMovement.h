#pragma once
#include "IMovementBehaviour.h"
#include <vec2.hpp>

class FallMovement : public IMovementBehaviour {
public:
    enum class FallType {
        SPAWNING,  // Straight down to target position
        DYING      // Directional fall with acceleration
    };

    FallMovement(FallType type, float duration = 1.0f, float acceleration = 9.8f);

    void Start(const glm::vec3& startWorld, const glm::vec3& targetWorld) override;
    bool Update(float deltaTime) override;
    glm::vec3 GetCurrentPosition() const override;
    void Reset() override;
    void SetDirection(const glm::vec2& direction);

private:
    FallType m_type;
    glm::vec3 m_startWorld;
    glm::vec3 m_targetWorld;
    glm::vec2 m_direction{ 0.f, 1.f };
    float m_progress = 0.f;
    float m_duration;
    float m_acceleration;
    bool m_isMoving = false;
};
