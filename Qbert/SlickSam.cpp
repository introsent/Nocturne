#include "SlickSam.h"
#include "Tile.h"
#include <random>
#include "Directions.h"

SlickSam::SlickSam(dae::GameObject* owner, Level* level,
    const IPositionProxy& qbertPositionProxy, bool isSlick)
    : SimpleEnemy(owner, level, qbertPositionProxy), m_isSlick(isSlick)
{

}

void SlickSam::GenerateNextMove() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution dist(0, 1);

    m_targetGridPos = m_currentGridPos + (dist(gen) ? DOWN_LEFT : DOWN_RIGHT);
}

void SlickSam::OnLand() {
    if (Tile* tile = GetLevel()->GetTileAt(m_currentGridPos)) {
        tile->RevertColor();
    }

    if (GetLevel()->IsOffGrid(m_currentGridPos)) {
        StartDying(false);
    }
}