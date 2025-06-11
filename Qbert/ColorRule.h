#pragma once
#include <vector>
#include <memory>

class Tile;

class ColorRule {
public:
    virtual ~ColorRule() = default;
    virtual void ConfigureTile(Tile& tile) const = 0;
    virtual void OnJump(Tile& tile) = 0;
    virtual bool IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const = 0;
    virtual bool IsTileCompleted(const Tile& tile) const = 0;
};

class OneHitRule final : public ColorRule {
public:
    void ConfigureTile(Tile& tile) const override;
    void OnJump(Tile& tile) override;
    bool IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const override;
    bool IsTileCompleted(const Tile& tile) const override;
};

class TwoHitRule final : public ColorRule {
public:
    void ConfigureTile(Tile& tile) const override;
    void OnJump(Tile& tile) override;
    bool IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const override;
    bool IsTileCompleted(const Tile& tile) const override;
};

class ToggleRule final : public ColorRule {
public:
    void ConfigureTile(Tile& tile) const override;
    void OnJump(Tile& tile) override;
    bool IsCompleted(const std::vector<std::unique_ptr<Tile>>& tiles) const override;
    bool IsTileCompleted(const Tile& tile) const override;
};