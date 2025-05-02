#pragma once
#include <vector>
#include <memory>

class Tile;

class ColorRule
{
public:
    virtual ~ColorRule() = default;

    // Called once during level load to assign starting and target colors
    virtual void Apply(Tile& tile) = 0;

    // Called when Q*Bert lands on a tile
    virtual void OnJump(Tile& tile) = 0;

    // Check if level is completed
    virtual bool IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const = 0;

    virtual bool IsTileCompleted(const Tile& tile) const = 0;
};

// One-hit rule: jump once to reach target color
class OneHitRule final : public ColorRule
{
public:
    void Apply(Tile& tile) override;
    void OnJump(Tile& tile) override;
    bool IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const override;
    bool IsTileCompleted(const Tile& tile) const override;
};

// Two-hit rule: jump twice, reaching intermediate then final
class TwoHitRule final : public ColorRule
{
public:
    void Apply(Tile& tile) override;
    void OnJump(Tile& tile) override;
    bool IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const override;
    bool IsTileCompleted(const Tile& tile) const override;
};

// Toggle rule: toggles between start and target color
class ToggleRule final : public ColorRule
{
public:
    void Apply(Tile& tile) override;
    void OnJump(Tile& tile) override;
    bool IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const override;
    bool IsTileCompleted(const Tile& tile) const override;
};
