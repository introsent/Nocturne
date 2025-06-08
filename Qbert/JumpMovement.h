#pragma once
#include <vec3.hpp>
#include <numbers>
#include <functional>
#include "glm.hpp"

class JumpMovement
{
public:
    using PositionConverter = std::function<glm::vec2(const glm::ivec2&)>;

    JumpMovement(PositionConverter gridToWorld);

    void StartJump(const glm::ivec2& startGrid, const glm::ivec2& targetGrid);

    bool Update(float deltaTime);

    glm::vec3 GetCurrentPosition() const;

    void SetJumpParameters(float duration, float height);

    bool IsJumping() const { return m_isJumping; }
    const glm::ivec2& GetTargetGrid() const { return m_targetGrid; }

private:
    PositionConverter m_gridToWorld;
    glm::ivec2 m_startGrid;
    glm::ivec2 m_targetGrid;
    glm::vec3 m_startWorld;
    glm::vec3 m_targetWorld;
    float m_progress = 0.f;
    float m_duration;
    float m_height;
    bool m_isJumping = false;
};

