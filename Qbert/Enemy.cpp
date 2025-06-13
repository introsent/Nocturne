#include "Enemy.h"
#include "utils.h"

Enemy::Enemy(dae::GameObject* owner, Level* level, const MultiQbertPositionProxy& qbertPositionProxy, PositionConverter converter)
	: Component(owner), m_pLevel(level), m_qbertPositionProxy(qbertPositionProxy), m_converter(converter) {
	m_pAnimation = owner->GetComponent<AnimationComponent>();
}

void Enemy::Update(float)
{
 	CheckQBertCollision();
}

void Enemy::MoveTo(const glm::ivec2& gridPos)
{
	m_currentGridPos = gridPos;
}

void Enemy::UpdateAnimation(int frame)
{
	m_pAnimation->SetFrame(frame);
}

void Enemy::ApplyScoreToScoreComponent(int score)
{
	m_pScore->AddScore(score);
}

void Enemy::LookAt(const glm::ivec2& direction)
{
	m_currentDirection = direction;
}

void Enemy::CheckQBertCollision()
{
	const glm::vec2 enemyPosition = GetOwner()->GetWorldPosition();
	const auto& proxies = m_qbertPositionProxy.GetAllProxies();
	for (const auto& proxy : proxies) {
		const glm::vec2 qbertPosition = proxy->GetWorldPosition();
		if (AreEnemyAndQbertClose(enemyPosition, qbertPosition)) {
			OnCollisionWithQbert.Invoke(GetOwner());
			break;
		}
	}
}
