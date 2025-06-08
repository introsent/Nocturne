#include "SnakeState.h"
#include "Enemy.h" 
#include "Coily.h"
#include "Directions.h"

void SnakeState::Enter(Coily*) {
    m_isDelaying = true;
    m_delayTimer = JUMP_DELAY;
}

std::unique_ptr<CoilyState> SnakeState::Update(Coily* coily, float deltaTime) {
    if (m_isDelaying) {
        m_delayTimer -= deltaTime;
        if (m_delayTimer <= 0.0f) {
            m_isDelaying = false;
            // Start new jump after delay
            m_targetGridPosition = CalculateChaseDirection(coily);
            m_jump.StartJump(coily->GetGridPosition(), m_targetGridPosition);
            m_isJumping = true;

            // Update animation
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

            // Start delay after landing
            m_isDelaying = true;
            m_delayTimer = JUMP_DELAY;

            coily->UpdateAnimation(DirectionToFrame(coily->GetCurrentLookAtDirection()));

            // Check for QBert collision
            if (coily->GetGridPosition() == coily->GetQBertGridPosition()) {
                // coily->m_pQBert->Die();
            }
        }
        else {
            owner->SetLocalPosition(m_jump.GetCurrentPosition());
        }
    }

    return nullptr;
}

glm::ivec2 SnakeState::CalculateChaseDirection(Coily* coily) {
    glm::ivec2 qbertPos = coily->GetQBertGridPosition();
    glm::ivec2 coilyPos = coily->GetGridPosition();
    glm::ivec2 bestMove = coilyPos;
    float minDistance = FLT_MAX;

    // Check all possible moves
    for (const auto& dir : { UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT }) {
        glm::ivec2 testPos = coilyPos + dir;

        float dist = glm::distance(glm::vec2(testPos), glm::vec2(qbertPos));
        if (dist < minDistance) {
            minDistance = dist;
            bestMove = testPos;
        }
       
    }
    return bestMove;
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