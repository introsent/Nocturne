#include "ColorRule.h"
#include "Tile.h"

// OneHitRule: 0(start) -> 1(target)
void OneHitRule::ConfigureTile(Tile& tile) const {
    tile.SetStartColor(0);
    tile.SetTargetColor(1);
    tile.SetColorIndex(0);
}

void OneHitRule::OnJump(Tile& tile) {
    if (!tile.HasReachedTarget()) tile.SetToTarget();
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
        if (!tile.IsInIntermediateState()) tile.SetToIntermediate();
        else tile.SetToTarget();
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
    if (tile.HasReachedTarget()) tile.SetToStart();
    else tile.SetToTarget();
}

bool ToggleRule::IsTileCompleted(const Tile& tile) const { return tile.GetColorIndex() == 1; }
bool ToggleRule::IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const {
    for (const auto& t : tiles) if (!t->HasReachedTarget()) return false;
    return true;
}