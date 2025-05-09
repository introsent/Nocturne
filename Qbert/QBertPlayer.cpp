#include "QBertPlayer.h"

#include <stdexcept>

#include "AnimationComponent.h"
#include "DeadState.h"
#include "IdleState.h"
#include "LevelComponent.h"
#include "Tile.h"
#include "utils.h"

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
    : Component(owner), m_pLevel(level)
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

    if (m_pLevel->GetTileAt(m_CurrentGridPos)->GetType() == TileType::DEATH && m_pCurrentState->GetName() != "Dead") {
        Die();
    }
}

void QBertPlayer::ChangeState(std::unique_ptr<QBertState> newState) {
    if (m_pCurrentState) {
        m_pCurrentState->Exit(GetOwner());
    }
    m_pCurrentState = std::move(newState);
    if (m_pCurrentState) {
        m_pCurrentState->Enter(GetOwner());
    }
}

bool QBertPlayer::TryStartJump(const glm::ivec2& direction) {
    if (m_pCurrentState->GetName() == "Dead") return false;

    const glm::ivec2 newPos = m_CurrentGridPos + direction;
    Tile* targetTile = m_pLevel->GetTileAt(newPos);

    if (targetTile) {

        // Valid movement
        m_CurrentDirection = direction;
        m_CurrentGridPos = newPos;
        m_JumpTargetPos = glm::vec3(GridToWorldCharacter(newPos), 0.f);
        return true;
    }

    // No tile exists (shouldn't happen with death border)
    return false;
}

void QBertPlayer::CompleteJump() {
    GetOwner()->SetLocalPosition(m_JumpTargetPos);
    m_pLevel->HandleJump(m_CurrentGridPos);
}

void QBertPlayer::Die() {
    if (m_pCurrentState->GetName() != "Dead") {
        ChangeState(std::make_unique<DeadState>());
    }
}

void QBertPlayer::Respawn() {
    m_CurrentGridPos = { 0,0 };
    GetOwner()->SetLocalPosition(glm::vec3(GridToWorldCharacter(m_CurrentGridPos), 0.f));
}

void QBertPlayer::UpdateSpriteDirection(const glm::ivec2& direction) {

    const glm::ivec2 UP_LEFT{ -1, -1 };
    const glm::ivec2 UP_RIGHT{ 0, -1 };
    const glm::ivec2 DOWN_LEFT{ 0, 1 };
    const glm::ivec2 DOWN_RIGHT{ 1, 1 };

    // Map grid directions to animation frames (adjust according to sprite sheet layout)
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