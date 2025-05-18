#include "QBertPlayer.h"
#include <stdexcept>
#include "AnimationComponent.h"
#include "DeadState.h"
#include "IdleState.h"
#include "LevelComponent.h"
#include "Tile.h"
#include "utils.h"

namespace {
    // Hash implementation for glm::ivec2 to use in unordered_map
    struct IVec2Hash {
        size_t operator()(const glm::ivec2& vec) const {
            // Combine hashes of x and y components using bit shifting
            return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
        }
    };
}

QBertPlayer::QBertPlayer(dae::GameObject* owner, Level* level)
    : Component(owner)
    , m_pLevel(level)
{
    m_pAnimation = GetOwner()->GetComponent<AnimationComponent>();
    if (!m_pAnimation) {
        throw std::runtime_error("QBertPlayer requires AnimationComponent");
    }
    ChangeState(std::make_unique<IdleState>());
}

void QBertPlayer::Update(float deltaTime) {
    if (m_pCurrentState) {
        m_pCurrentState->Update(GetOwner(), deltaTime);
    }
}

// --- State Management ---
void QBertPlayer::ChangeState(std::unique_ptr<QBertState> newState) {
    if (m_pCurrentState) {
        m_pCurrentState->Exit(GetOwner());
    }
    m_pCurrentState = std::move(newState);
    if (m_pCurrentState) {
        m_pCurrentState->Enter(GetOwner());
    }
}



// --- Lifecycle Management ---
void QBertPlayer::Die() {
    if (m_pCurrentState->GetName() != "Dead") {
        ChangeState(std::make_unique<DeadState>());
    }
}

void QBertPlayer::Respawn() {
    // Reset to starting position (top of pyramid)
    m_CurrentGridPos = { 0,0 };
    GetOwner()->SetLocalPosition(glm::vec3(GridToWorldCharacter(m_CurrentGridPos), 0.f));
}

bool QBertPlayer::CanAcceptInput() const
{
    return m_pCurrentState ? m_pCurrentState->CanAcceptInput() : false;
}

// --- Animation System ---
void QBertPlayer::UpdateSpriteDirection(const glm::ivec2& direction) const
{
    // Direction vectors relative to grid movement
    const glm::ivec2 UP_LEFT{ -1, -1 };   // Northwest movement
    const glm::ivec2 UP_RIGHT{ 0, -1 };   // Northeast movement
    const glm::ivec2 DOWN_LEFT{ 0, 1 };   // Southwest movement
    const glm::ivec2 DOWN_RIGHT{ 1, 1 };  // Southeast movement

    // Mapping of grid directions to animation frames:
    // 0 = Up-Right, 1 = Up-Left, 2 = Down-Right, 3 = Down-Left
    const static std::unordered_map<glm::ivec2, int, IVec2Hash> directionMap = {
        {UP_RIGHT,  0},
        {UP_LEFT,   1},
        {DOWN_RIGHT, 2},
        {DOWN_LEFT, 3}
    };

    if (const auto it = directionMap.find(direction); it != directionMap.end()) {
        m_pAnimation->SetFrame(it->second);
    }
}
