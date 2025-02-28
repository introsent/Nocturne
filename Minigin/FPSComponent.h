#pragma once
#include "Component.h"

namespace dae
{
    class FPSComponent : public Component
    {
    public:
        FPSComponent(GameObject* owner); 
        void Update(float deltaTime) override;

        [[nodiscard]] float GetFPS() const { return m_FPS; }

    private:
        float m_FPS{ 0.0f };
    };
}
