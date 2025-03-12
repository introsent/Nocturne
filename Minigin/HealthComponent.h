#pragma once
#include <iostream>

#include "Component.h"
#include "Subject.h"

namespace dae
{
    class HealthComponent : public Component, public Subject {
    public:
        HealthComponent(GameObject* owner, int lives);

        void TakeDamage();

        int GetLives() const;

    private:
        int m_lives;
    };
}


