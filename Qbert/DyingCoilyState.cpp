#include "DyingCoilyState.h"
#include "Coily.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include <SoundServiceLocator.h>

DyingCoilyState::DyingCoilyState(dae::GameObject* owner)
    : CoilyState(owner),
    m_fallMovement(std::make_unique<FallMovement>(
        FallMovement::FallType::DYING,
        1.5f,
        15.0f
    ))
{
}

void DyingCoilyState::Enter(Coily* coily) {
    m_owner->GetComponent<dae::TextureComponent>()->SetDepth(-1.f);
    const glm::ivec2 dir = coily->GetCurrentLookAtDirection();

    glm::vec2 fallDirection;
    if (glm::length(glm::vec2(dir)) > 0) {
        fallDirection = glm::normalize(glm::vec2(dir));
    }
    else {
        fallDirection = { 1.0f, 0.5f };
    }

    fallDirection.y = std::abs(fallDirection.y);
    m_fallMovement->SetDirection(fallDirection);

    m_fallStart = m_owner->GetWorldPosition();

    const float fallDistance = 500.0f;
    glm::vec3 fallTarget = m_fallStart +
        glm::vec3(fallDirection.x * fallDistance,
            fallDirection.y * fallDistance,
            0.0f);

    if (fallTarget.y < m_fallStart.y) {
        fallTarget.y = m_fallStart.y + fallDistance;
    }

    m_fallMovement->Start(m_fallStart, fallTarget);
    dae::SoundServiceLocator::GetService()->PlaySound("coily_fall");

    if (auto enemy = m_owner->GetComponent<Enemy>()) {
        enemy->ApplyScoreToScoreComponent(500);
    }
}

std::unique_ptr<CoilyState> DyingCoilyState::Update(Coily* coily, float deltaTime) {
    if (m_fallMovement->Update(deltaTime)) {
        if (coily->IsPlayerControlled()) {
            // Respawn Coily in Versus mode
            coily->MoveTo({ 0, 0 });
            return std::make_unique<SpawningState>(m_owner);
        }
        m_owner->MarkForDestroy();
        return nullptr;
    }

    const glm::vec3 fallMovementPosition = m_fallMovement->GetCurrentPosition();
    m_owner->SetLocalPosition(glm::vec3(fallMovementPosition.x, fallMovementPosition.y, -0.5f));

    return nullptr;
}

void DyingCoilyState::Exit(Coily*) {
    m_fallMovement->Reset();
}