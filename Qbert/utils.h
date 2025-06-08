#pragma once
#include <vec2.hpp>

constexpr float TileWidth = 64.f;
constexpr float TileHeight = 48.f;
constexpr glm::vec2 Origin{ 300.f, 100.f };

inline glm::vec2 GridToWorldEx(
    const glm::ivec2& gridPos,
    const glm::vec2& spriteSize = { 0, 0 },
    const glm::vec2& entityOffset = { 0, 0 }
) {
    const float baseX = Origin.x + (gridPos.x - gridPos.y / 2.0f) * TileWidth;
    const float baseY = Origin.y + gridPos.y * TileHeight;

    glm::vec2 centerOffset = { 0, 0 };
    if (spriteSize.x > 0 && spriteSize.y > 0) {
        centerOffset = {
            (TileWidth - spriteSize.x) * 0.5f,
            (TileHeight - spriteSize.y) * 0.5f
        };
    }

    return { baseX + centerOffset.x + entityOffset.x,
            baseY + centerOffset.y + entityOffset.y };
}

inline glm::vec2 GridToWorld(const glm::ivec2& gridPos) {
    return GridToWorldEx(gridPos, { 0, 0 }, { 0, 0 });
}

inline glm::vec2 GridToWorldCoily(const glm::ivec2& gridPos) {
    constexpr glm::vec2 CoilyOffset{ TileWidth * 0.25f, -TileHeight * 0.8f };
    return GridToWorldEx(gridPos, { 0, 0 }, CoilyOffset);
}

inline glm::vec2 GridToWorldCharacter(const glm::ivec2& gridPos) {
    constexpr glm::vec2 CharOffset{ TileWidth * 0.25f, -TileHeight * 0.25f };
    return GridToWorldEx(gridPos, { 0, 0 }, CharOffset);
}

inline glm::vec2 GridToWorldDisc(const glm::ivec2& gridPos, const glm::vec2& spriteSize) {
    return GridToWorldEx(gridPos, spriteSize, { 0, 0 });
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