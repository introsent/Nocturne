#include "SpawningState.h"
#include "Level.h"
#include "Enemy.h" 
#include "Coily.h"
#include "Directions.h"

SpawningState::SpawningState(dae::GameObject* owner)
    : CoilyState(owner),
    m_fallMovement(std::make_unique<FallMovement>(
        FallMovement::FallType::SPAWNING,  // Use spawning fall type
        1.2f,
        0.0f))  // No acceleration for spawning
{
}

void SpawningState::Enter(Coily* coily) {
    const auto gridPos = coily->GetDesiredSpawnGridPosition();
    m_spawnTarget = glm::vec3(GridToWorldCoily(gridPos), 0.f);

    m_spawnStart = m_spawnTarget;
    m_spawnStart.y -= 300.f; 

    m_owner->SetLocalPosition(m_spawnStart);
    m_fallMovement->Start(m_spawnStart, m_spawnTarget);
    coily->UpdateAnimation(0); 

    coily->MoveTo(gridPos);
}

std::unique_ptr<CoilyState> SpawningState::Update(Coily*, float deltaTime) {
    if (m_fallMovement->Update(deltaTime)) {
        m_owner->SetLocalPosition(m_spawnTarget);
        return std::make_unique<EggState>(m_owner); 
    }

    m_owner->SetLocalPosition(m_fallMovement->GetCurrentPosition());
    return nullptr;
}

void SpawningState::Exit(Coily*) {
    m_fallMovement->Reset();
}