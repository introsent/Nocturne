#include "TextureComponent.h"

#include <SDL_render.h>

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Component.h"

namespace dae
{
    TextureComponent::TextureComponent(GameObject* owner, const std::string& textureFile)
        : Component(owner)
    {
        SetTexture(textureFile);  // Initialize texture when component is created
    }

    void TextureComponent::Render() const
    {
        if (m_texture)
        {
            if (auto owner = GetOwner())  // Get the owner directly from base class (GameObject*)
            {
              
                const auto pos = owner->GetWorldPosition();
                Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);  // Render the texture using the owner's position
                
            }
        }
    }

    void TextureComponent::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);  // Load texture using ResourceManager
    }
}
