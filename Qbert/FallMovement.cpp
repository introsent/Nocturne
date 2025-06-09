#include "FallMovement.h"
#include <algorithm>
#include <common.hpp>
#include <geometric.hpp>

FallMovement::FallMovement(FallType type, float duration, float acceleration)
    : m_type(type), m_duration(duration), m_acceleration(acceleration) {
}

void FallMovement::Start(const glm::vec3& startWorld, const glm::vec3& targetWorld) {
    m_startWorld = startWorld;
    m_targetWorld = targetWorld;
    m_progress = 0.f;
    m_isMoving = true;
}

bool FallMovement::Update(float deltaTime) {
    if (!m_isMoving) return true;

    m_progress += deltaTime / m_duration;
    m_progress = std::clamp(m_progress, 0.0f, 1.0f);
    return m_progress >= 1.0f;
}

glm::vec3 FallMovement::GetCurrentPosition() const {
    switch (m_type) {
    case FallType::SPAWNING:
        // Linear vertical fall for spawning
        return {
            m_targetWorld.x,  // Keep X fixed
            glm::mix(m_startWorld.y, m_targetWorld.y, m_progress),
            m_targetWorld.z   // Keep Z fixed
        };

    case FallType::DYING:
        // Directional fall with acceleration
        const float t = m_progress;
        const float easedT = t * t;
        const float horizontalProgress = easedT;
        const float verticalOffset = m_acceleration * easedT * 100.f;

        return {
            m_startWorld.x + m_direction.x * horizontalProgress * 200.f,
            m_startWorld.y + verticalOffset,
            m_startWorld.z
        };
    }
    return m_targetWorld;
}

void FallMovement::Reset() {
    m_progress = 0.f;
    m_isMoving = false;
}

void FallMovement::SetDirection(const glm::vec2& direction) {
    m_direction = glm::normalize(direction);
}