#include "Level.h"
#include "Tile.h"
#include "ColorRule.h"

Level::Level(int levelNumber, int numRows)
    : m_rows(numRows)
{
    switch (levelNumber)
    {
    case 1: m_colorRule = std::make_unique<OneHitRule>();    break;
    case 2: m_colorRule = std::make_unique<TwoHitRule>();    break;
    case 3: m_colorRule = std::make_unique<ToggleRule>();    break;
    default: m_colorRule = std::make_unique<OneHitRule>();   break;
    }
    CreateTiles();
    ApplyInitialRule();
}

Level::~Level() = default;

void Level::CreateTiles()
{
    m_tiles.clear();
    m_tiles.reserve(m_rows * (m_rows + 1) / 2);

    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col <= row; ++col)
        {
            m_tiles.push_back(std::make_unique<Tile>(glm::ivec2{ col, row }));
        }
    }
}

void Level::ApplyInitialRule()
{
    for (auto& tilePtr : m_tiles)
    {
        m_colorRule->Apply(*tilePtr);
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
