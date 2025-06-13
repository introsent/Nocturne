#include "SlickSam.h"
#include "Tile.h"
#include <random>
#include "Directions.h"
#include "utils.h"

SlickSam::SlickSam(dae::GameObject* owner, Level* level, glm::ivec2 spawnGridPosition,
    const MultiQbertPositionProxy& qbertPositionProxy, bool isSlick)
    : SimpleEnemy(owner, level, spawnGridPosition, qbertPositionProxy, [this](const glm::ivec2& grid) { return GridToWorldSamSlick(grid); }), m_isSlick(isSlick)
{
}

void SlickSam::GenerateNextMove() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution dist(0, 1);

    int chosenDirection = dist(gen);
    UpdateAnimation(chosenDirection);
    m_targetGridPos = m_currentGridPos + (chosenDirection ? DOWN_RIGHT : DOWN_LEFT);
}

void SlickSam::OnLand() {
    if (Tile* tile = GetLevel()->GetTileAt(m_currentGridPos)) {
        tile->RevertColor();
    }

    if (GetLevel()->IsOffGrid(m_currentGridPos)) {
        StartDying(false);
    }
}