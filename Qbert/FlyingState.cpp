#include "FlyingState.h"
#include "QBertPlayer.h"
#include "Level.h"
#include "DiscManager.h"
#include "AnimationComponent.h"
#include "IdleState.h"
#include "utils.h"
#include <SoundServiceLocator.h>

FlyingState::FlyingState(dae::GameObject* owner)
    : QBertState(owner) {}

void FlyingState::Enter(QBertPlayer* player) {
    m_originalParent = owner->GetParent(); // store original parent 
    InitializeFlight(player);
}

void FlyingState::InitializeFlight(QBertPlayer* player) {
    m_phaseTimer = 0.f;
    m_currentPhase = FlyingPhase::Flying;

    // Get disc reference (non-owning)
    m_pDisc = DiscManager::GetInstance().GetDiscAt(player->GetGridPosition());
    if (!m_pDisc) return;

    // Cache positions
    m_qbertStartPos = owner->GetWorldPosition();
    m_discStartPos = m_pDisc->GetWorldPosition();
    m_targetWorldPos = CalculateElevatedPosition();
    m_landingWorldPos = CalculateTopPosition();

    // Start disc animation
    if (auto* anim = m_pDisc->GetComponent<AnimationComponent>()) {
        anim->SetAutoAdvance(true);
    }
    dae::SoundServiceLocator::GetService()->PlaySound("disk_lift");
}

const glm::vec3 FlyingState::CalculateTopPosition() const {
    const glm::vec2 topWorld = GridToWorldCharacter({ 0, 0 });
    return { topWorld.x, topWorld.y, 0.f };
}

const glm::vec3 FlyingState::CalculateElevatedPosition() const {
    glm::vec3 pos = CalculateTopPosition();
    pos.y -= TileHeight;  // Elevated position
    return pos;
}

std::unique_ptr<QBertState> FlyingState::Update(QBertPlayer* player, float deltaTime) {
    switch (m_currentPhase) {
    case FlyingPhase::Flying:
        UpdateFlyingPhase(deltaTime);
        break;

    case FlyingPhase::Dropping:
        UpdateDroppingPhase(deltaTime);
        break;

    case FlyingPhase::Complete:
        return CompleteFlight(player);
    }
    return nullptr;
}

void FlyingState::UpdateFlyingPhase(float deltaTime) {
    m_phaseTimer += deltaTime;
    const float t = glm::clamp(m_phaseTimer / m_flightDuration, 0.f, 1.f);

    // Interpolate positions
    if (m_pDisc) {
        m_pDisc->SetLocalPosition(glm::mix(m_discStartPos, m_targetWorldPos, t));
        owner->SetParent(m_pDisc);
		owner->SetLocalPosition(m_qbertLocalOffset); 
    }

    // Transition to dropping phase
    if (t >= 1.0f) {
        if (m_pDisc) {
            m_pDisc->MarkForDestroy();
            m_pDisc = nullptr;
            owner->SetParent(m_originalParent);
        }
        dae::SoundServiceLocator::GetService()->PlaySound("disk_land");
        m_phaseTimer = 0.f;
        m_currentPhase = FlyingPhase::Dropping;
        owner->SetLocalPosition(m_targetWorldPos);
    }
}

void FlyingState::UpdateDroppingPhase(float deltaTime) {
    m_phaseTimer += deltaTime;
    const float t = glm::clamp(m_phaseTimer / m_dropDuration, 0.f, 1.f);

    // Drop to landing position
    const glm::vec3 newPos = glm::mix(m_targetWorldPos, m_landingWorldPos, t);
    owner->SetLocalPosition(newPos);

    // Transition to complete
    if (t >= 1.0f) {
        owner->SetLocalPosition(m_landingWorldPos);
        m_currentPhase = FlyingPhase::Complete;
    }
}

std::unique_ptr<QBertState> FlyingState::CompleteFlight(QBertPlayer* player) {
    player->MoveTo({ 0, 0 });
    player->GetLevel()->HandleJump(player->GetGridPosition());
    return std::make_unique<IdleState>(owner);
}