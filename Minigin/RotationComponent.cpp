#include "RotationComponent.h"

void dae::RotationComponent::Update(float deltaTime)
{
    if (GetOwner())
    {
        m_angle += m_rotationSpeed * deltaTime;
        if (m_angle >= 360.f)
            m_angle -= 360.f;

        glm::vec3 newLocalPos(
            m_radius * cos(glm::radians(m_angle)),
            m_radius * sin(glm::radians(m_angle)),
            0.f
        );

        GetOwner()->SetLocalPosition(newLocalPos);
    }
}
