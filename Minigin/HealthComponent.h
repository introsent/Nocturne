#pragma once
#include <iostream>

#include "Component.h"
#include "Event.h"

namespace dae
{
    class HealthComponent : public Component {
    public:
        HealthComponent(GameObject* pOwner) : Component(pOwner) {}

        // event triggered whenever health changes.
        Event<> OnHealthChanged;

        void TakeDamage();

        int GetLives() const;

    private:
        int m_lives = 3;
    };
}


