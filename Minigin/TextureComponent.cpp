#include "TextureComponent.h"
#include <SDL_render.h>
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Component.h"

namespace dae
{
    TextureComponent::TextureComponent(GameObject* owner, const std::string& textureFile, float depth, float scale)
        : Component(owner)
        , m_depth(depth)
        , m_scale(scale)
    {
        SetTexture(textureFile);
    }

    void TextureComponent::Render() const
    {
        if (m_texture && GetOwner())
        {
            const auto pos = GetOwner()->GetWorldPosition();
            if (m_srcRect.z == 0.f && m_srcRect.w == 0.f)
            {
                const glm::vec4 source{ 0.f, 0.f, static_cast<float>(m_texture->GetSize().x), static_cast<float>(m_texture->GetSize().y) };
                Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, source, m_scale);
            }
            else
            {
                Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_srcRect, m_scale);
            }
        }
    }

    void TextureComponent::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
    }

    void TextureComponent::SetSrcRect(const glm::vec4& srcRect)
    {
        m_srcRect = srcRect;
    }

    void TextureComponent::SetDepth(float depth)
    {
        m_depth = depth;
    }
}