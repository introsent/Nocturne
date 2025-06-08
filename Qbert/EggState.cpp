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
    if (m_jump.Update(deltaTime))
    {
        coily->MoveTo(m_jump.GetTargetGrid());

        if (coily->GetGridPosition().y == coily->GetLevel()->GetRows() - 1)
        {
            return std::make_unique<SnakeState>(owner);
        }
        else
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, 1);

            GenerateTargetGridPosition(coily);
            m_jump.StartJump(coily->GetGridPosition(), m_targetGridPosition);
        }
        coily->UpdateAnimation(0);
	}
	else
	{
		coily->UpdateAnimation(1);
	}

    owner->SetLocalPosition(m_jump.GetCurrentPosition());


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
