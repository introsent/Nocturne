#include "JumpMovement.h"
#include <algorithm>
#include <common.hpp>

JumpMovement::JumpMovement(PositionConverter converter,
    float duration,
    float height)
    : GridBasedMovement(converter),
    m_duration(duration),
    m_height(height) {
}

void JumpMovement::Start(const glm::ivec2& startGrid,
    const glm::ivec2& targetGrid) {
    m_startGrid = startGrid;
    m_targetGrid = targetGrid;
    m_startWorld = glm::vec3(m_converter(startGrid), 0.f);
    m_targetWorld = glm::vec3(m_converter(targetGrid), 0.f);
    m_progress = 0.f;
    m_isMoving = true;
}

void JumpMovement::Start(const glm::vec3&,
    const glm::vec3&) {
    // Not used for grid-based movement
}

bool JumpMovement::Update(float deltaTime) {
    if (!m_isMoving) return true;

    m_progress += deltaTime / m_duration;
    m_progress = std::clamp(m_progress, 0.0f, 1.0f);

    if (m_progress >= 1.0f) {
        m_isMoving = false;
        return true;
    }
    return false;
}

glm::vec3 JumpMovement::GetCurrentPosition() const {
    const float t = m_progress;
    const float yOffset = sin(t * std::numbers::pi_v<float>) * m_height;
    const glm::vec3 basePos = glm::mix(m_startWorld, m_targetWorld, t);
    return { basePos.x, basePos.y - yOffset, basePos.z };
}

void JumpMovement::Reset() {
    m_progress = 0.f;
    m_isMoving = false;
}

void JumpMovement::SetParameters(float duration, float height) {
    m_duration = duration;
    m_height = height;
}