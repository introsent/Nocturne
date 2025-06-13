#include "SnakeState.h"
#include "Enemy.h" 
#include "Coily.h"
#include "Directions.h"
#include "utils.h"
#include "Tile.h"
#include "DyingCoilyState.h"
#include <SoundServiceLocator.h>

void SnakeState::Enter(Coily*) {
    m_isDelaying = true;
    m_delayTimer = JUMP_DELAY;
}

std::unique_ptr<CoilyState> SnakeState::Update(Coily* coily, float deltaTime) {
    if (coily->IsPlayerControlled()) {
        if (m_isJumping) {
            if (m_jump.Update(deltaTime)) {
                coily->MoveTo(m_targetGridPosition);
                m_isJumping = false;
                if (ShouldDie(coily)) {
                    return std::make_unique<DyingCoilyState>(m_owner);
                }
            }
            else {
                m_owner->SetLocalPosition(m_jump.GetCurrentPosition());
            }
        }
        return nullptr;
    }

    if (m_isDelaying) {
        m_delayTimer -= deltaTime;
        if (m_delayTimer <= 0.0f) {
            m_isDelaying = false;
            m_targetGridPosition = CalculateChaseDirection(coily);
            m_jump.Start(coily->GetGridPosition(), m_targetGridPosition);
            m_isJumping = true;
            dae::SoundServiceLocator::GetService()->PlaySound("coily_snake_jump");

            const glm::ivec2 direction = m_targetGridPosition - coily->GetGridPosition();
            coily->LookAt(direction);
            coily->UpdateAnimation(DirectionToFrame(direction));
        }
        return nullptr;
    }

    if (m_isJumping) {
        if (m_jump.Update(deltaTime)) {
            coily->MoveTo(m_targetGridPosition);
            m_isJumping = false;
            m_isDelaying = true;
            m_delayTimer = JUMP_DELAY;

            coily->UpdateAnimation(DirectionToFrame(coily->GetCurrentLookAtDirection()));

            if (ShouldDie(coily)) {
                return std::make_unique<DyingCoilyState>(m_owner);
            }
        }
        else {
            m_owner->SetLocalPosition(m_jump.GetCurrentPosition());
        }
    }

    return nullptr;
}
void SnakeState::HandleInput(Coily* coily, const glm::ivec2& direction)
{
    if (!m_isJumping) {
        m_targetGridPosition = coily->GetGridPosition() + direction;
        m_jump.Start(coily->GetGridPosition(), m_targetGridPosition);
        m_isJumping = true;
        dae::SoundServiceLocator::GetService()->PlaySound("coily_snake_jump");
        coily->LookAt(direction);
        coily->UpdateAnimation(DirectionToFrame(direction));
    }
}

glm::ivec2 SnakeState::CalculateChaseDirection(Coily* coily) {
    glm::ivec2 qbertGridPosition = coily->GetQBertGridPosition();
    glm::ivec2 coilyGridPosition = coily->GetGridPosition();

    glm::ivec2 bestMoveGridPosition = coilyGridPosition;
    float minDistanceToQbert = FLT_MAX;

    for (const auto& dir : { UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT }) {
        glm::ivec2 testPos = coilyGridPosition + dir;

        float distance = glm::distance(glm::vec2(testPos), glm::vec2(qbertGridPosition));
        if (distance < minDistanceToQbert) {
            minDistanceToQbert = distance;
            bestMoveGridPosition = testPos;
        }
    }
    return bestMoveGridPosition;
}

int SnakeState::DirectionToFrame(const glm::ivec2& dir) {
    static const std::unordered_map<glm::ivec2, int, IVec2Hash> mapping = {
        {UP_RIGHT, 2}, {UP_LEFT, 4}, {DOWN_RIGHT, 6}, {DOWN_LEFT, 8}
    };
    if (m_isJumping)
    {
        return mapping.at(dir) + 1;
    }
    return mapping.at(dir);
}

bool SnakeState::ShouldDie(Coily* coily) const
{
    return coily->GetLevel()->GetTileAt(coily->GetGridPosition())->GetType() == TileType::DEATH;
}
