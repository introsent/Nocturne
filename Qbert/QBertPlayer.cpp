#include "QBertPlayer.h"
#include "AnimationComponent.h"
#include "DeadState.h"
#include "IdleState.h"
#include "LevelComponent.h"
#include "Tile.h"
#include "utils.h"
#include <stdexcept>

QBertPlayer::QBertPlayer(dae::GameObject* owner, Level* level)
    : Component(owner), m_pLevel(level)
{
    m_pAnimation = GetOwner()->GetComponent<AnimationComponent>();
    if (!m_pAnimation) {
        throw std::runtime_error("QBertPlayer requires AnimationComponent");
    }
    TransitionTo(std::make_unique<IdleState>(owner));
}

void QBertPlayer::Update(float deltaTime) {
    if (m_pCurrentState) {
        if (auto newState = m_pCurrentState->Update(this, deltaTime)) {
            TransitionTo(std::move(newState));
        }
    }
}

void QBertPlayer::HandleInput(const glm::ivec2& direction) {
    if (m_pCurrentState && m_pCurrentState->CanAcceptInput()) {
        if (auto newState = m_pCurrentState->HandleInput(this, direction)) {
            TransitionTo(std::move(newState));
        }
    }
}

void QBertPlayer::TransitionTo(std::unique_ptr<QBertState> newState) {
    if (m_pCurrentState) {
        m_pCurrentState->Exit(this);
    }

    m_pCurrentState = std::move(newState);

    if (m_pCurrentState) {
        m_pCurrentState->Enter(this);
    }
}

void QBertPlayer::MoveTo(const glm::ivec2& gridPos) {
    m_CurrentGridPos = gridPos;
    GetOwner()->SetLocalPosition(glm::vec3(GridToWorldCharacter(gridPos), 0.f));
}

void QBertPlayer::LookAt(const glm::ivec2& direction)
{
    m_CurrentDirection = direction;
}

// --- Animation System ---
void QBertPlayer::UpdateAnimation() 
{
    // Direction vectors relative to grid movement
    const glm::ivec2 UP_LEFT{ -1, -1 };   // North-west movement
    const glm::ivec2 UP_RIGHT{ 0, -1 };   // North-east movement
    const glm::ivec2 DOWN_LEFT{ 0, 1 };   // South-west movement
    const glm::ivec2 DOWN_RIGHT{ 1, 1 };  // South-east movement

    // Mapping of grid directions to animation frames:
    // 0 = Up-Right, 1 = Up-Left, 2 = Down-Right, 3 = Down-Left
    const static std::unordered_map<glm::ivec2, int, IVec2Hash> directionMap = {
        {UP_RIGHT,  0},
        {UP_LEFT,   1},
        {DOWN_RIGHT, 2},
        {DOWN_LEFT, 3}
    };

    if (const auto it = directionMap.find(m_CurrentDirection); it != directionMap.end()) {
        m_pAnimation->SetFrame(it->second);
    }
}


void QBertPlayer::Respawn() {
    MoveTo({ 0, 0 });
}
