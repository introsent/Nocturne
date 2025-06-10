#pragma once
#include <memory>
#include <string>
#include <vec3.hpp>
#include "GameObject.h"
#include "TextureComponent.h"
#include "TranslationComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "AnimationComponent.h"

class GameObjectBuilder {
public:
    GameObjectBuilder() : object(std::make_unique<dae::GameObject>()) {}

    // Add a texture component and store it for animation
    GameObjectBuilder& WithTexture(const std::string& textureFile, float depth, float scale) {
        textureComp = object->AddComponent<dae::TextureComponent>(object.get(), textureFile, depth, scale);
        return *this;
    }

    // Add a translation component
    GameObjectBuilder& WithTranslation() {
        object->AddComponent<dae::TranslationComponent>(object.get());
        return *this;
    }

    // Add a text component
    GameObjectBuilder& WithText(const std::string& text, std::shared_ptr<dae::Font> font) {
        object->AddComponent<dae::TextComponent>(object.get(), text, font);
        return *this;
    }

    // Add an FPS component
    GameObjectBuilder& WithFPS() {
        object->AddComponent<dae::FPSComponent>(object.get());
        return *this;
    }

    // Add a health component and optionally output the pointer
    GameObjectBuilder& WithHealth(dae::HealthComponent** outHealth = nullptr) {
        auto comp = object->AddComponent<dae::HealthComponent>(object.get());
        if (outHealth)
            *outHealth = comp;
        return *this;
    }

    // Add a score component and optionally output the pointer
    GameObjectBuilder& WithScore(dae::ScoreComponent** outScore = nullptr) {
        auto comp = object->AddComponent<dae::ScoreComponent>(object.get());
        if (outScore)
            *outScore = comp;
        return *this;
    }

    // Add an animation component using the stored texture component
    GameObjectBuilder& WithAnimation(const glm::vec2& frameSize, int totalFrames, float timePerFrame, int rows, int columns) {
        if (textureComp) {
            object->AddComponent<AnimationComponent>(object.get(), textureComp, frameSize, totalFrames, timePerFrame, rows, columns);
        }
        return *this;
    }

    // Generic method to add any component
    template <typename T, typename... Args>
    GameObjectBuilder& WithComponent(Args&&... args) {
        object->AddComponent<T>(object.get(), std::forward<Args>(args)...);
        return *this;
    }

    // Set the local position of the GameObject
    GameObjectBuilder& SetPosition(const glm::vec3& pos) {
        object->SetLocalPosition(pos);
        return *this;
    }

    // Return the fully built GameObject
    std::unique_ptr<dae::GameObject> Build() {
        return std::move(object);
    }

private:
    std::unique_ptr<dae::GameObject> object;
    dae::TextureComponent* textureComp = nullptr; // Store texture component for animation
};
