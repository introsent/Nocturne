#include "SimpleEnemy.h"
#include "FallMovement.h"
#include "utils.h"
#include "MovementRunner.h"

SimpleEnemy::SimpleEnemy(dae::GameObject* owner, Level* level,
    const IPositionProxy& qbertPositionProxy, PositionConverter converter)
    : Enemy(owner, level, qbertPositionProxy, converter),
    m_jumpMovement(converter)
{
  
}

void SimpleEnemy::Update(float deltaTime) {
    if (m_isDying) return;

    if (m_isWaiting) {
        m_delayTimer -= deltaTime;
        if (m_delayTimer <= 0) {
            GenerateNextMove();
            m_jumpMovement.Start(m_currentGridPos, m_targetGridPos);
            m_isWaiting = false;
            m_isJumping = true;
        }
    }
    else if (m_isJumping) {
        if (m_jumpMovement.Update(deltaTime)) {
            MoveTo(m_targetGridPos);
            OnLand();
            m_isJumping = false;
            m_isWaiting = true;
            m_delayTimer = JUMP_DELAY;
        }
        else {
            GetOwner()->SetLocalPosition(m_jumpMovement.GetCurrentPosition());
        }
    }
}

void SimpleEnemy::StartDying(bool byQbert)
{
    m_isDying = true;
    auto fall = std::make_unique<FallMovement>(FallMovement::FallType::DYING, 1.5f, 15.0f);
    fall->SetDirection(glm::vec2(byQbert ? 1.0f : -1.0f, 0.5f));
    fall->Start(GetOwner()->GetWorldPosition(),
        GetOwner()->GetWorldPosition() + glm::vec3(200, 300, 0));

    GetOwner()->AddComponent<MovementRunner>(std::move(fall), [this] {  
        GetOwner()->MarkForDestroy();  
    }, GetOwner());
}
