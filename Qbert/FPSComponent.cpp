#include "FPSComponent.h"
#include <format>
#include "GameObject.h"
#include "TextComponent.h"

namespace dae
{
    FPSComponent::FPSComponent(GameObject* owner) : Component(owner) {}

    void FPSComponent::Update(float deltaTime)
    {
        if (deltaTime > 0.0f) 
            m_FPS = 1.0f / deltaTime;

        if (auto owner = GetOwner()) 
        {
            if (auto textComponent = owner->GetComponent<TextComponent>()) 
            {
                textComponent->SetText(std::format("{:.1f}", m_FPS) + " FPS"); 
            }
        }
    }
}
