#include "JumpMovement.h"
#include <algorithm>

JumpMovement::JumpMovement(PositionConverter gridToWorld) : m_gridToWorld(gridToWorld)
{
	SetJumpParameters(0.5f, 32.f);
}

void JumpMovement::StartJump(const glm::ivec2& startGrid, const glm::ivec2& targetGrid)
{
    m_startGrid = startGrid;
    m_targetGrid = targetGrid;
    m_startWorld = glm::vec3(m_gridToWorld(startGrid), 0.f);
    m_targetWorld = glm::vec3(m_gridToWorld(targetGrid), 0.f);
    m_progress = 0.f;
    m_isJumping = true;
}

bool JumpMovement::Update(float deltaTime)
{
    if (!m_isJumping) return true;

    m_progress += deltaTime / m_duration;
    m_progress = std::clamp(m_progress, 0.0f, 1.0f);

    if (m_progress >= 1.0f) {
        m_isJumping = false;
        return true;
    }
    return false;
}

glm::vec3 JumpMovement::GetCurrentPosition() const
{
    const float t = m_progress;
    const float yOffset = sinf(t * std::numbers::pi_v<float>) * m_height;
    const glm::vec3 basePos = glm::mix(m_startWorld, m_targetWorld, t);
    return { basePos.x, basePos.y - yOffset, basePos.z };
}

void JumpMovement::SetJumpParameters(float duration, float height)
{
    m_duration = duration;
    m_height = height;
}
