#include "Tile.h"

Tile::Tile(const glm::ivec2& gridPos)
    : m_colorIndex(m_startColor)
    , m_gridPos(gridPos)
{
}

glm::vec2 Tile::GetWorldPosition() const
{
    // isometric conversion: adjust values in the future
    constexpr float TileW = 64.f;
    constexpr float TileH = 32.f;
    constexpr glm::vec2 Origin{ 400.f, 100.f };

    int row = m_gridPos.y;
    int col = m_gridPos.x;
    float x = Origin.x + (col - row * 0.5f) * TileW;
    float y = Origin.y + row * (TileH * 0.75f);
    return { x, y };
}

glm::ivec2 Tile::GetGridPosition() const
{
    return m_gridPos;
}

int Tile::GetColorIndex() const
{
    return m_colorIndex;
}

void Tile::SetColorIndex(int index)
{
    m_colorIndex = index;
}

void Tile::SetOccupied(bool occupied)
{
    m_isOccupied = occupied;
}

bool Tile::IsOccupied() const
{
    return m_isOccupied;
}

void Tile::SetToStart()
{
    m_colorIndex = m_startColor;
}

void Tile::SetToIntermediate()
{
    if (m_intermediateColor != -1)
        m_colorIndex = m_intermediateColor;
}

void Tile::SetToTarget()
{
    m_colorIndex = m_targetColor;
}

bool Tile::HasReachedTarget() const
{
    return m_colorIndex == m_targetColor;
}

bool Tile::IsInIntermediateState() const
{
    return m_colorIndex == m_intermediateColor;
}
