#include "Enemy.h"
#include "utils.h"

Enemy::Enemy(dae::GameObject* owner, Level* level, const IPositionProxy& qbertPositionProxy, PositionConverter converter)
	: Component(owner), m_pLevel(level), m_qbertPositionProxy(qbertPositionProxy), m_converter(converter) {
	m_pAnimation = owner->GetComponent<AnimationComponent>();
}

void Enemy::Update(float)
{
}

void Enemy::MoveTo(const glm::ivec2& gridPos)
{
	m_currentGridPos = gridPos;
	GetOwner()->SetLocalPosition(glm::vec3(m_converter(gridPos), 0.f));
	CheckQBertCollision();
}

void Enemy::UpdateAnimation(int frame)
{
	m_pAnimation->SetFrame(frame);
}

void Enemy::LookAt(const glm::ivec2& direction)
{
	m_currentDirection = direction;
}

void Enemy::CheckQBertCollision()
{
	if (m_currentGridPos == m_qbertPositionProxy.GetGridPosition()) {
		OnCollisionWithQbert.Invoke(GetOwner());
	}
}
