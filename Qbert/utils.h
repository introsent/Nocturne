#pragma once
#include <vec2.hpp>

constexpr float TileWidth = 64.f;
constexpr float TileHeight = 48.f;

inline glm::vec2 GridToWorld(const glm::ivec2& gridPos) {
    constexpr glm::vec2 Origin{ 300.f, 100.f };

// For regular triangle spacing
    int row = gridPos.y;
    int col = gridPos.x;

    // Center each row horizontally
    float x = Origin.x + (col - row / 2.f) * TileWidth;
    float y = Origin.y + row * TileHeight;

    return { x, y };
}

inline glm::vec2 GridToWorldCharacter(const glm::ivec2& gridPos) {
    
    constexpr glm::vec2 Origin{ 300.f, 100.f };
    constexpr glm::vec2 CharacterOffset{ TileWidth * 0.25f, -TileHeight * 0.25f };

    // Base position (same as tiles)
    float x = Origin.x + (gridPos.x - gridPos.y / 2.f) * TileWidth;
    float y = Origin.y + gridPos.y * TileHeight;

    // Apply character-specific offset
    return { x + CharacterOffset.x, y + CharacterOffset.y };
    
}

inline glm::vec2 GridToWorldDisc(const glm::ivec2& gridPos, const glm::vec2& spriteSize) {
    constexpr glm::vec2 Origin{ 300.f, 100.f };
    float x = Origin.x + (gridPos.x - gridPos.y / 2.f) * TileWidth;
    float y = Origin.y + gridPos.y * TileHeight;


    glm::vec2 cellCenterOffset{
        (TileWidth - spriteSize.x) * 0.5f,
        (TileHeight - spriteSize.y) * 0.5f  
    };

    return { x + cellCenterOffset.x, y + cellCenterOffset.y };
}

// Hash implementation for glm::ivec2 to use in unordered_map
struct IVec2Hash {
    size_t operator()(const glm::ivec2& vec) const {
        // Combine hashes of x and y components using bit shifting
        return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
    }
};

struct IVec2Equal {
    bool operator()(glm::ivec2 const& a, glm::ivec2 const& b) const noexcept {
        return a.x == b.x && a.y == b.y;
    }
};