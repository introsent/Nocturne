#include "Enemy.h"
#include "utils.h"

void Enemy::Update(float)
{
}

void Enemy::MoveTo(const glm::ivec2& gridPos)
{
	m_currentGridPos = gridPos;
	GetOwner()->SetLocalPosition(glm::vec3(GridToWorldCoily(gridPos), 0.f));
	CheckQBertCollision();
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
