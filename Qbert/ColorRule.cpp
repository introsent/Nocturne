#include "ColorRule.h"
#include "Tile.h"

// OneHitRule: 0(start) -> 1(target)
void OneHitRule::ConfigureTile(Tile& tile) const {
    tile.SetStartColor(0);
    tile.SetTargetColor(1);
    tile.SetColorIndex(0);
}

void OneHitRule::OnJump(Tile& tile) {
    if (!tile.HasReachedTarget()) {
        tile.ChangeColor(1);  // Changed to use event-driven system
    }
}

bool OneHitRule::IsTileCompleted(const Tile& tile) const { return tile.GetColorIndex() == 1; }
bool OneHitRule::IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const {
    for (const auto& t : tiles) if (!t->HasReachedTarget()) return false;
    return true;
}

// TwoHitRule: 0 -> 1 -> 2
void TwoHitRule::ConfigureTile(Tile& tile) const {
    tile.SetStartColor(0);
    tile.SetIntermediateColor(1);
    tile.SetTargetColor(2);
    tile.SetColorIndex(0);
}

void TwoHitRule::OnJump(Tile& tile) {
    if (!tile.HasReachedTarget()) {
        tile.ChangeColor(1);  // Always advance color
    }
}

bool TwoHitRule::IsTileCompleted(const Tile& tile) const { return tile.GetColorIndex() == 2; }
bool TwoHitRule::IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const {
    for (const auto& t : tiles) if (!t->HasReachedTarget()) return false;
    return true;
}

// ToggleRule: 0 <-> 1
void ToggleRule::ConfigureTile(Tile& tile) const {
    tile.SetStartColor(0);
    tile.SetTargetColor(1);
    tile.SetColorIndex(0);
}

void ToggleRule::OnJump(Tile& tile) {
    // Toggle between start and target
    tile.ChangeColor(tile.HasReachedTarget() ? -1 : 1);
}

bool ToggleRule::IsTileCompleted(const Tile& tile) const { return tile.GetColorIndex() == 1; }
bool ToggleRule::IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const {
    for (const auto& t : tiles) if (!t->HasReachedTarget()) return false;
    return true;
}