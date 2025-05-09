#include "QBertPlayer.h"

#include <iostream>

#include "utils.h"
#include <numbers>
#include <stdexcept>

// Anonymous namespace for hash implementation (avoiding global scope pollution)
namespace {
    // Custom hash implementation for glm::ivec2 to enable use in unordered_map
    struct IVec2Hash {
        size_t operator()(const glm::ivec2& vec) const {
            // Combine hashes of x and y components using bitwise operations
            // Note: XOR with shifted bits helps prevent collisions for similar values
            return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
        }
    };
}

QBertPlayer::QBertPlayer(dae::GameObject* owner, Level* level)
    : Component(owner), m_pLevel(level), m_CurrentGridPos{ 0,0 }  // Initialize at pyramid top
{
    // Cache animation component reference for efficient updates
    m_pAnimation = GetOwner()->GetComponent<AnimationComponent>();

    // Validate critical component dependencies
    if (!m_pAnimation) {
        throw std::runtime_error("QBertPlayer requires AnimationComponent");
    }
}

void QBertPlayer::Update(float deltaTime) {
    if (!m_IsJumping) return;

    // Calculate normalized jump progress [0..1]
    m_JumpProgress += deltaTime / m_JumpDuration;

    // Cubic easing function for smooth acceleration/deceleration
    float t = m_JumpProgress;
    t = t < 0.5f ? 4 * t * t * t : 1 - powf(-2 * t + 2, 3) / 2;

    // Parabolic arc calculation using sine wave for jump effect
    const float yOffset = sinf(t * static_cast<float>(std::numbers::pi)) * m_JumpHeight;

    // Interpolate position between start and target with vertical offset
    const glm::vec3 newPos = glm::mix(m_JumpStartPos, m_JumpTargetPos, t);
    GetOwner()->SetLocalPosition({ newPos.x, newPos.y - yOffset, newPos.z });

    // Finalize jump when progress completes
    if (m_JumpProgress >= 1.f) {
        CompleteJump();
    }
}

void QBertPlayer::JumpTo(const glm::ivec2& targetGridPos) {
    // Validate movement initialization
    if (m_IsJumping) return;

    // Configure jump parameters
    m_IsJumping = true;
    m_JumpProgress = 0.f;
    m_CurrentGridPos = targetGridPos;

    // Calculate world positions using grid conversion functions
    m_JumpStartPos = GetOwner()->GetWorldPosition();
    m_JumpTargetPos = glm::vec3(GridToWorldCharacter(targetGridPos), 0.f);
}

bool QBertPlayer::TryMove(const glm::ivec2& inputDirection) {
    // Prevent mid-air movement
    if (m_IsJumping) return false;

    // Calculate target grid position
    const glm::ivec2 newPos = m_CurrentGridPos + inputDirection;

    // Debug output for movement validation
    std::cout << "Movement attempt: ("
        << m_CurrentGridPos.x << "," << m_CurrentGridPos.y << ") -> ("
        << newPos.x << "," << newPos.y << ")\n";

    // Validate target tile existence
    if (auto targetTile = m_pLevel->GetTileAt(newPos)) {
        UpdateSpriteDirection(inputDirection);
        JumpTo(newPos);
        return true;
    }
    return false;
}

void QBertPlayer::CompleteJump() {
    // Finalize jump state
    m_IsJumping = false;

    // Snap to final position to prevent floating point inaccuracies
    GetOwner()->SetLocalPosition(m_JumpTargetPos);

    // Notify level system about successful landing
    m_pLevel->HandleJump(m_CurrentGridPos);
}

void QBertPlayer::UpdateSpriteDirection(const glm::ivec2& direction) {
    // Direction-to-animation frame mapping
    // Note: Directions assume Q*bert's diagonal pyramid movement pattern
    constexpr glm::ivec2 UP_LEFT{ -1, -1 };   
    constexpr glm::ivec2 UP_RIGHT{ 0, -1 };     
    constexpr glm::ivec2 DOWN_LEFT{ 0, 1 };    
    constexpr glm::ivec2 DOWN_RIGHT{ 1, 1 };    

    // Map grid directions to animation frames (adjust according to sprite sheet layout)
    const static std::unordered_map<glm::ivec2, int, IVec2Hash> directionMap = {
        {UP_RIGHT,  0}, 
        {UP_LEFT,   1},  
        {DOWN_RIGHT, 2},
        {DOWN_LEFT, 3}   
    };

    // Update animation frame if valid direction found
    if (const auto it = directionMap.find(direction); it != directionMap.end()) {
        m_pAnimation->SetFrame(it->second);
    }
}