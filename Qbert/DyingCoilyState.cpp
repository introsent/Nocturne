#include "DyingCoilyState.h"
#include "Coily.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

DyingCoilyState::DyingCoilyState(dae::GameObject* owner)
    : CoilyState(owner),
    m_fallMovement(std::make_unique<FallMovement>(
        FallMovement::FallType::DYING,
        1.5f,  // Duration
        15.0f  // Acceleration
    ))
{

}

void DyingCoilyState::Enter(Coily* coily) {
    m_owner->GetComponent<dae::TextureComponent>()->SetDepth(-1.f);
    // Determine fall direction based on current orientation
    const glm::ivec2 dir = coily->GetCurrentLookAtDirection();

    // Convert to normalized world direction
    glm::vec2 fallDirection;
    if (glm::length(glm::vec2(dir)) > 0) {
        fallDirection = glm::normalize(glm::vec2(dir));
    }
    else {
        // Default to right if no direction
        fallDirection = { 1.0f, 0.5f };
    }

    // Flip Y direction for falling down
    fallDirection.y = std::abs(fallDirection.y);
    m_fallMovement->SetDirection(fallDirection);

    // Set start position to current position
    m_fallStart = m_owner->GetWorldPosition();

    // Calculate target position (off-screen)
    const float fallDistance = 500.0f;
    glm::vec3 fallTarget = m_fallStart +
        glm::vec3(fallDirection.x * fallDistance,
            fallDirection.y * fallDistance,
            0.0f);

    // Ensure it's going downward off-screen
    if (fallTarget.y < m_fallStart.y) {
        fallTarget.y = m_fallStart.y + fallDistance;
    }

    // Start the fall movement
    m_fallMovement->Start(m_fallStart, fallTarget);
}

std::unique_ptr<CoilyState> DyingCoilyState::Update(Coily*, float deltaTime) {
    if (m_fallMovement->Update(deltaTime)) {
        // Fall complete - destroy the object
        m_owner->MarkForDestroy();
        return nullptr;
    }

    // Update position during fall
    const glm::vec3 fallMovementPosition = m_fallMovement->GetCurrentPosition();
    m_owner->SetLocalPosition(glm::vec3(fallMovementPosition.x, fallMovementPosition.y, -0.5f));


    return nullptr;
}

void DyingCoilyState::Exit(Coily*) {
    m_fallMovement->Reset();
}
