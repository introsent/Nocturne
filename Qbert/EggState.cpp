#include "EggState.h"
#include "Enemy.h" 
#include "Coily.h"
#include "Directions.h"
#include <random>

void EggState::Enter(Coily* coily)
{
    GenerateTargetGridPosition(coily);
	m_jump.StartJump(coily->GetGridPosition(), m_targetGridPosition);
	coily->UpdateAnimation(0);
}

std::unique_ptr<CoilyState> EggState::Update(Coily* coily, float deltaTime)
{
    if (m_isDelaying) {
        m_delayTimer -= deltaTime;
        if (m_delayTimer <= 0.0f) {
            m_isDelaying = false;

            GenerateTargetGridPosition(coily);
            m_jump.StartJump(coily->GetGridPosition(), m_targetGridPosition);
        }
        return nullptr;
    }

    if (m_jump.Update(deltaTime)) {
        coily->MoveTo(m_jump.GetTargetGrid());
        m_owner->SetLocalPosition(m_jump.GetCurrentPosition());

        if (coily->GetGridPosition().y == coily->GetLevel()->GetRows() - 1) {
            return std::make_unique<SnakeState>(m_owner);
        }
        else {
            // Start delay after landing
            m_isDelaying = true;
            m_delayTimer = JUMP_DELAY;
            coily->UpdateAnimation(0);  // Idle frame
        }
    }
    else {
        // During jump
        m_owner->SetLocalPosition(m_jump.GetCurrentPosition());
        coily->UpdateAnimation(1);  // Jump frame
    }

    return nullptr;
}

void EggState::Exit(Coily*)
{
   
}

void EggState::GenerateTargetGridPosition(Coily* coily)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1);

	m_targetGridPosition = coily->GetGridPosition() + (dist(gen) ? DOWN_RIGHT : DOWN_LEFT);
}
