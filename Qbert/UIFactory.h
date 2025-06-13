// UIFactory.h
#pragma once
#include <memory>
#include <vec3.hpp>
#include "GameObjectBuilder.h"

// Factory function to create a UI text element.
inline std::unique_ptr<dae::GameObject> CreateUIText(const std::string& text, std::shared_ptr<dae::Font> font, const glm::vec3& pos) {
    return GameObjectBuilder()
        .WithText(text, font)
        .SetPosition(pos)
        .Build();
}
