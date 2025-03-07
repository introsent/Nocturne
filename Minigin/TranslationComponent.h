#pragma once
#include "Component.h"


namespace dae
{
    class TranslationComponent : public Component
    {
    public:
        TranslationComponent(GameObject* owner);

        void Translate(const glm::vec3& offset) const;

    };

}
