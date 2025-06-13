#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include <SDL_pixels.h>

namespace dae
{
    class Font;
    class Texture2D;

    class TextComponent final : public Component
    {
    public:
        // Constructor now takes raw pointer to GameObject
        TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font);
        ~TextComponent() override = default;

        void Update([[maybe_unused]] float deltaTime) override;
        void Render() const override;

        // Set the text, marks for update
        void SetText(const std::string& text);

		void SetColor(const SDL_Color& color);

        // Deleted copy/move constructors and assignment operators
        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;

    private:
        bool m_needsUpdate;
        std::string m_text;
        std::shared_ptr<Font> m_font;
        std::shared_ptr<Texture2D> m_textTexture;

		SDL_Color m_color{ 255, 255, 255, 255 };
    };
}
