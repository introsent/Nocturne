#include "UggWrongway.h"
#include "Directions.h"
#include "utils.h"
#include <iostream>
#include <random>

UggWrongway::UggWrongway(dae::GameObject* owner, Level* level, glm::ivec2 spawnGridPosition,
    const IPositionProxy& qbertPositionProxy, bool isUgg)
    : SimpleEnemy(owner, level, spawnGridPosition, qbertPositionProxy, [this](const glm::ivec2& grid) { return GridToWorldSamSlick(grid); }), m_isUgg(isUgg)
{
    OnLand();
}

void UggWrongway::GenerateNextMove() {
    m_targetGridPos = m_currentGridPos + m_direction;
}

void UggWrongway::OnLand()
{ 
    if (GetLevel()->IsOffGrid(m_currentGridPos)) {
        StartDying(false);
        return;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);

    const bool chooseUp = dist(gen);

    if (m_isUgg)
    {
        m_direction = chooseUp ? UP_LEFT : LEFT;
    }
    else
    {
        m_direction = chooseUp ? UP_RIGHT : RIGHT;
    }

    auto it = std::find(SPRITE_DIRECTIONS.begin(), SPRITE_DIRECTIONS.end(), m_direction);
    if (it != SPRITE_DIRECTIONS.end()) {
        int spriteIndex = static_cast<int>(std::distance(SPRITE_DIRECTIONS.begin(), it));
        UpdateAnimation((m_isUgg ? 0 : 4) + spriteIndex);
    }
    
  
}