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

class GameObjectBuilder {
public:
    GameObjectBuilder() : object(std::make_shared<dae::GameObject>()) {}

    // Add a texture component
    GameObjectBuilder& WithTexture(const std::string& textureFile) {
        object->AddComponent<dae::TextureComponent>(object.get(), textureFile);
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

    // Set the local position of the GameObject
    GameObjectBuilder& SetPosition(const glm::vec3& pos) {
        object->SetLocalPosition(pos);
        return *this;
    }

    // Return the fully built GameObject
    std::shared_ptr<dae::GameObject> Build() {
        return object;
    }

private:
    std::shared_ptr<dae::GameObject> object;
};
#pragma once
