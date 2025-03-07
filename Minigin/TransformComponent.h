#pragma once
#include "Component.h"
#include "Transform.h"
#include <memory>

namespace dae
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent(GameObject* owner);

        const glm::vec3& GetPosition() const;
        void SetPosition(float x, float y, float z);

        void SetLocalPosition(const glm::vec3& position);
        const glm::vec3& GetLocalPosition() const;

        void Translate(const glm::vec3& offset);

        void Update(float deltaTime) override;

    private:
        Transform m_transform; 
    };
}
