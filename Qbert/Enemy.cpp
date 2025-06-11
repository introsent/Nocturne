#include "Enemy.h"
#include "utils.h"

void Enemy::Update(float)
{
}

void Enemy::MoveTo(const glm::ivec2& gridPos)
{
	m_currentGridPos = gridPos;
	GetOwner()->SetLocalPosition(glm::vec3(GridToWorldCoily(gridPos), 0.f));
}

void Enemy::LookAt(const glm::ivec2& direction)
{
	m_currentDirection = direction;
}
