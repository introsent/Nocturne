#include "QBertPlayer.h"

#include <numbers>
#include <functional>
#include <iostream>
#include <SDL_stdinc.h>

#include "utils.h"

namespace {
    struct IVec2Hash {
        size_t operator()(const glm::ivec2& vec) const {
            return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
        }
    };
}


QBertPlayer::QBertPlayer(dae::GameObject* owner, Level* level)
    : Component(owner), m_pLevel(level), m_CurrentGridPos{ 0,0 }
{
    //m_pTranslation = GetOwner()->GetComponent<dae::TranslationComponent>();
    m_pAnimation = GetOwner()->GetComponent<AnimationComponent>();
}

void QBertPlayer::Update(float deltaTime) {
    if (!m_IsJumping) return;

    m_JumpProgress += deltaTime / m_JumpDuration;

    // Cubic easing
    float t = m_JumpProgress;
    t = t < 0.5f ? 4 * t * t * t : 1 - powf(-2 * t + 2, 3) / 2;

    // Parabolic arc
    float yOffset = sinf(t * static_cast<float>(std::numbers::pi)) * m_JumpHeight;

    // Direct position update through GameObject
    glm::vec3 newPos = glm::mix(m_JumpStartPos, m_JumpTargetPos, t);
    newPos.y -= yOffset;
    GetOwner()->SetLocalPosition(newPos);

    if (m_JumpProgress >= 1.f) {
        CompleteJump();
    }
}

void QBertPlayer::JumpTo(const glm::ivec2& targetGridPos) {
    m_IsJumping = true;
    m_JumpProgress = 0.f;
    m_JumpStartPos = GetOwner()->GetWorldPosition(); // Get current position directly
    m_JumpTargetPos = glm::vec3(GridToWorldCharacter(targetGridPos), 0.f);
    m_CurrentGridPos = targetGridPos;
}



bool QBertPlayer::TryMove(const glm::ivec2& inputDirection) {
    if (m_IsJumping) return false;

    glm::ivec2 newPos = m_CurrentGridPos + inputDirection;

    // Add debug output to verify grid calculations
    std::cout << "Trying to move from (" << m_CurrentGridPos.x << "," << m_CurrentGridPos.y
        << ") to (" << newPos.x << "," << newPos.y << ")\n";

    if (auto targetTile = m_pLevel->GetTileAt(newPos)) {
        UpdateSpriteDirection(inputDirection);
        JumpTo(newPos);
        return true;
    }
    return false;
}

void QBertPlayer::CompleteJump() {
    m_IsJumping = false;
    GetOwner()->SetLocalPosition(m_JumpTargetPos);
    m_pLevel->HandleJump(m_CurrentGridPos);
}

void QBertPlayer::UpdateSpriteDirection(const glm::ivec2& direction) {

    const glm::ivec2 UP_LEFT{ -1, -1 };
    const glm::ivec2 UP_RIGHT{ 0, -1 };
    const glm::ivec2 DOWN_LEFT{ 0, 1 };
    const glm::ivec2 DOWN_RIGHT{ 1, 1 };

    const static std::unordered_map<glm::ivec2, int, IVec2Hash> directionMap = {

        {UP_RIGHT,  0},  // Up-Left
        {UP_LEFT,   1},  // Up-Right
        {DOWN_RIGHT,2},  // Down-Left
        {DOWN_LEFT, 3}   // Down-Right
    };

    if (auto it = directionMap.find(direction); it != directionMap.end()) {
        m_pAnimation->SetFrame(it->second);
    }
}