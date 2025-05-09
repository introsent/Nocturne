#include "Level.h"
#include "Tile.h"
#include "ColorRule.h"
Level::Level(int levelNumber, int numRows)
    : m_levelNumber(levelNumber),
    m_rows(numRows)
{
    switch (m_levelNumber) {
    case 1: m_colorRule = std::make_unique<OneHitRule>(); break;
    case 2: m_colorRule = std::make_unique<TwoHitRule>(); break;
    case 3: m_colorRule = std::make_unique<ToggleRule>(); break;
    default: m_colorRule = std::make_unique<OneHitRule>(); break;
    }
    CreateTiles();
    ConfigureTiles();
}

Level::~Level() = default;

void Level::CreateTiles() {
    m_tiles.clear();

    for (int row = 0; row < m_rows; ++row) {
        // Generate columns for this row (row + 1 tiles)
        for (int col = 0; col <= row; ++col) {
            // Center tiles under the previous row
            int centeredCol = col - (row / m_rows);
            m_tiles.push_back(std::make_unique<Tile>(glm::ivec2{ centeredCol, row }));
        }
    }

    CreateDeathBorder();
}
void Level::ConfigureTiles() const
{
    for (auto& tilePtr : m_tiles) {
        m_colorRule->ConfigureTile(*tilePtr);
    }
}
void Level::CreateDeathBorder() {
    // Create death tiles around the main pyramid
    for (int row = -1; row <= m_rows; ++row) {
        // Determine column range for this row
        int minCol = -1;
        int maxCol = (row >= -1 && row < m_rows) ? row + 1 : m_rows + 1;

        for (int col = minCol; col <= maxCol; ++col) {
            // Match the original pyramid's column centering logic
            int centeredCol = col - (row >= -1 && row < m_rows ? row / m_rows : 0);
            glm::ivec2 pos{ centeredCol, row };

            // Skip positions that exist in main pyramid
            if (!GetTileAt(pos)) {
                m_tiles.push_back(std::make_unique<Tile>(pos, TileType::DEATH));
            }
        }
    }
}

void Level::HandleJump(const glm::ivec2& gridPos)
{
    if (m_hasCompleted) return;

    if (auto tile = GetTileAt(gridPos))
    {
        int before = tile->GetColorIndex();
        m_colorRule->OnJump(*tile);
        int after = tile->GetColorIndex();

        if (after != before && m_colorRule->IsTileCompleted(*tile))
        {
            OnTileColored.Invoke(*tile);
        }
        if (m_colorRule->IsCompleted(m_tiles))
        {
            m_hasCompleted = true;
            OnLevelCompleted.Invoke();
        }
    }
}

bool Level::IsCompleted() const
{
    return m_hasCompleted;
}

Tile* Level::GetTileAt(const glm::ivec2& gridPos) const
{
    for (auto& tilePtr : m_tiles)
    {
        if (tilePtr->GetGridPosition() == gridPos)
            return tilePtr.get();
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Tile>>& Level::GetTiles() const
{
    return m_tiles;
}
