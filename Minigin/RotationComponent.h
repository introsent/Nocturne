#pragma once
#include "Component.h"

namespace dae
{
    class RotationComponent : public Component
    {
    public:
        RotationComponent(GameObject* pOwner, float radius, float rotationSpeed)
            : Component(pOwner), m_radius(radius), m_rotationSpeed(rotationSpeed), m_angle(0.f) {
        }

        void Update(float deltaTime) override;

    private:
        float m_radius;         
        float m_rotationSpeed; 
        float m_angle;      
    };
}
