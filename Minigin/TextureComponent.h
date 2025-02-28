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
        TextureComponent(GameObject* owner, const std::string& textureFile);  // Change constructor to take raw pointer (GameObject*)
        void Update(float) override {}
        void Render() const override;

        void SetTexture(const std::string& filename);

    private:
        std::shared_ptr<Texture2D> m_texture;
    };
}
