#pragma once

#include "Component.h"
#include "Texture2D.h"
#include <memory>
#include <string>

namespace dae
{
    class TextureComponent : public Component
    {
    public:
        TextureComponent(GameObject* owner, const std::string& textureFile, float depth = 0.f, float scale = 1.f); 
        void Update(float) override {}
        void Render() const override;

        void SetTexture(const std::string& filename);
        void SetSrcRect(const glm::vec4& srcRect);
        void SetDepth(float depth);
        float GetDepth() const { return m_depth; }

    private:
        std::shared_ptr<Texture2D> m_texture;
        glm::vec4 m_srcRect{ 0.f, 0.f, 0.f, 0.f };
        float m_scale{ 1.f };
        float m_depth{ 0.f };  // New depth member
    };
}