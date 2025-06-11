#include "QbertPositionProxy.h"
#include "utils.h"

QbertPositionProxy::QbertPositionProxy(QBertPlayer* qbertPlayer)
	: m_pQBertPlayer(qbertPlayer),
	m_gridPosition(qbertPlayer->GetGridPosition()) 
{
}
glm::ivec2 QbertPositionProxy::GetGridPosition() const noexcept
{
	return m_gridPosition;
}

glm::vec2 QbertPositionProxy::GetWorldPosition() const noexcept
{
	return GridToWorldCharacter(m_gridPosition);
}

void QbertPositionProxy::UpdatePosition(const glm::ivec2& newPos)
{
	m_gridPosition = newPos;
}
