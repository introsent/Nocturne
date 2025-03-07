#include "TransformComponent.h"
#include "GameObject.h"

namespace dae
{
    TransformComponent::TransformComponent(GameObject* owner)
        : Component(owner) 
    {
    }

    const glm::vec3& TransformComponent::GetPosition() const
    {
        return m_transform.GetWorldPosition();
    }

    void TransformComponent::SetPosition(float x, float y, float z)
    {
        m_transform.SetWorldPosition(x, y, z);
    }

    void TransformComponent::SetLocalPosition(const glm::vec3& position)
    {
        m_transform.SetLocalPosition(position.x, position.y, position.z);
    }

    const glm::vec3& TransformComponent::GetLocalPosition() const
    {
        return m_transform.GetLocalPosition();
    }

    void TransformComponent::Translate(const glm::vec3& offset)
    {
        glm::vec3 currentPos = GetLocalPosition();
        SetLocalPosition(currentPos + offset);
    }

    void TransformComponent::Update(float)
    {
    }
}
