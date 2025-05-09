#pragma once
#include <vec2.hpp>

inline glm::vec2 GridToWorld(const glm::ivec2& gridPos) {
    constexpr glm::vec2 Origin{ 300.f, 100.f };
    constexpr float TileWidth = 64.f;
    constexpr float TileHeight = 48.f; // For regular triangle spacing

    int row = gridPos.y;
    int col = gridPos.x;

    // Center each row horizontally
    float x = Origin.x + (col - row / 2.f) * TileWidth;
    float y = Origin.y + row * TileHeight;

    return { x, y };
}

inline glm::vec2 GridToWorldCharacter(const glm::ivec2& gridPos) {
    
    constexpr glm::vec2 Origin{ 300.f, 100.f };
    constexpr float TileWidth = 64.f;
    constexpr float TileHeight = 48.f;
    constexpr glm::vec2 CharacterOffset{ TileWidth * 0.25f, -TileHeight * 0.25f };

    // Base position (same as tiles)
    float x = Origin.x + (gridPos.x - gridPos.y / 2.f) * TileWidth;
    float y = Origin.y + gridPos.y * TileHeight;

    // Apply character-specific offset
    return { x + CharacterOffset.x, y + CharacterOffset.y };
    
}
