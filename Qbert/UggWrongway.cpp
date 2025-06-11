#include "UggWrongway.h"
#include "Directions.h"

UggWrongway::UggWrongway(dae::GameObject* owner, Level* level,
    const IPositionProxy& qbertPositionProxy, bool isUgg)
    : SimpleEnemy(owner, level, qbertPositionProxy), m_isUgg(isUgg)
{
    m_directionSequence = isUgg ?
        std::vector{ UP_RIGHT, UP_LEFT } :
        std::vector{ UP_LEFT, UP_RIGHT };
}

void UggWrongway::GenerateNextMove() {
    m_targetGridPos = m_currentGridPos + m_directionSequence[m_currentDirectionIndex];
    m_currentDirectionIndex = (m_currentDirectionIndex + 1) % m_directionSequence.size();
}

void UggWrongway::OnLand() {
    if (GetLevel()->IsOffGrid(m_currentGridPos)) {
        StartDying(false);
    }
}