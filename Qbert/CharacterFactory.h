#pragma once
#include <memory>
#include <vec3.hpp>
#include "GameObjectBuilder.h"

// Factory function to create a character with texture, translation, health, and score components.
inline std::shared_ptr<dae::GameObject> CreateCharacter(const std::string& texture, float depth, float scale, const glm::vec3& pos,
    HealthComponent** outHealth = nullptr,
    ScoreComponent** outScore = nullptr)
{
    return GameObjectBuilder()
        .WithTexture(texture, depth, scale)
        .WithTranslation()
        .WithHealth(outHealth)
        .WithScore(outScore)
        .SetPosition(pos)
        .Build();
}
