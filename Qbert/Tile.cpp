#include "Tile.h"

Tile::Tile(const glm::ivec2& gridPos, TileType type)
    : m_type(type), m_gridPos(gridPos), m_colorIndex(m_startColor) {
}

// Color state configuration
void Tile::SetStartColor(int color) { m_startColor = color; }
void Tile::SetIntermediateColor(int color) { m_intermediateColor = color; }
void Tile::SetTargetColor(int color) { m_targetColor = color; }

// State transitions
void Tile::SetToStart() { m_colorIndex = m_startColor; }
void Tile::SetToIntermediate() {
    if (m_intermediateColor != -1) m_colorIndex = m_intermediateColor;
}
void Tile::SetToTarget() { m_colorIndex = m_targetColor; }

// New color change system
void Tile::ChangeColor(int change) {
    int newColor = m_colorIndex + change;

    // Prevent negative colors
    if (newColor < 0) newColor = 0;

    // Prevent exceeding target color
    if (m_intermediateColor != -1 && newColor > m_targetColor) {
        newColor = m_targetColor;
    }

    if (m_colorIndex != newColor) {
        m_colorIndex = newColor;
        OnColorChanged.Invoke(*this);
    }
}

void Tile::RevertColor() {
    ChangeColor(-1);
}

// Queries
bool Tile::HasReachedTarget() const { return m_colorIndex == m_targetColor; }
bool Tile::IsInIntermediateState() const { return m_colorIndex == m_intermediateColor; }
int Tile::GetColorIndex() const { return m_colorIndex; }
void Tile::SetColorIndex(int index) { m_colorIndex = index; }

// Position/Occupancy
glm::ivec2 Tile::GetGridPosition() const { return m_gridPos; }
bool Tile::IsOccupied() const { return m_isOccupied; }
void Tile::SetOccupied(bool occupied) { m_isOccupied = occupied; }