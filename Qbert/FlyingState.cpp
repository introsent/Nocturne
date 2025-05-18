#include "FlyingState.h"
#include "Level.h"
#include "QBertPlayer.h"
#include "LevelComponent.h"
#include "utils.h"
#include "AnimationComponent.h"
#include <TranslationComponent.h>
#include "IdleState.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DiscManager.h"

void FlyingState::Enter(dae::GameObject* player)
{
    auto* qbert = player->GetComponent<QBertPlayer>();
    const glm::ivec2 currentGridPos = qbert->GetCurrentGridPos();

    // Get the disc under Q*bert
    m_pDiscObject = DiscManager::GetInstance().GetDiscAt(currentGridPos);
    if (!m_pDiscObject)
        return;

    // Store starting positions
    m_qbertStartPos = player->GetWorldPosition();
    m_discStartPos = m_pDiscObject->GetWorldPosition();

    // Define the target top-of-grid position (elevated position)
    const glm::ivec2 topGridPos{ 0, 0 };
    const glm::vec2 topWorldPos2D = GridToWorldCharacter(topGridPos);
    m_targetWorldPos = glm::vec3(topWorldPos2D.x, topWorldPos2D.y - TileHeight, 0.f);

    // Store the actual grid position for the drop phase
    m_actualTopPos = glm::vec3(topWorldPos2D.x, topWorldPos2D.y, 0.f);

    // Start disc animation if available
    if (auto* anim = m_pDiscObject->GetComponent<AnimationComponent>())
    {
        anim->SetAutoAdvance(true);
    }

    m_flyTimer = 0.f;
    m_currentPhase = FlyingPhase::Flying;
}

void FlyingState::Update(dae::GameObject* player, float deltaTime)
{
    m_flyTimer += deltaTime;

    switch (m_currentPhase)
    {
    case FlyingPhase::Flying:
    {
        const float t = glm::clamp(m_flyTimer / m_flyDuration, 0.f, 1.f);

        // Smoothly interpolate Q*bert and disc positions
        const glm::vec3 qbertPos = glm::mix(m_qbertStartPos, m_targetWorldPos, t);
        const glm::vec3 discPos = glm::mix(m_discStartPos, m_targetWorldPos, t);

        player->SetLocalPosition(qbertPos);
        if (m_pDiscObject)
            m_pDiscObject->SetLocalPosition(discPos);

        // Once the flight is complete
        if (t >= 1.0f)
        {
            // Remove the disc from the scene
            if (m_pDiscObject)
            {
                m_pDiscObject->MarkForDestroy();
                m_pDiscObject.reset();
            }

            // Reset timer for the dropping phase
            m_flyTimer = 0.f;
            m_currentPhase = FlyingPhase::Dropping;

            // Set Q*bert to the elevated position
            player->SetLocalPosition(m_targetWorldPos);
        }
    }
    break;

    case FlyingPhase::Dropping:
    {
        const float t = glm::clamp(m_flyTimer / m_dropDuration, 0.f, 1.f);

        // Drop Q*bert from elevated position to actual grid position
        const glm::vec3 qbertPos = glm::mix(m_targetWorldPos, m_actualTopPos, t);
        player->SetLocalPosition(qbertPos);

        // Once the drop is complete
        if (t >= 1.0f)
        {
            // Snap Q*bert to the final position
            player->SetLocalPosition(m_actualTopPos);

            // Update Q*bert's logical position
            auto* qbert = player->GetComponent<QBertPlayer>();
            qbert->SetCurrentGridPos({ 0, 0 });

            m_currentPhase = FlyingPhase::Complete;

            // Switch to idle state
            qbert->ChangeState(std::make_unique<IdleState>());
        }
    }
    break;

    case FlyingPhase::Complete:
        // Already transitioning to IdleState, nothing to do here
        break;
    }
}