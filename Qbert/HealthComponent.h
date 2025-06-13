#pragma once
#include <iostream>

#include "Component.h"
#include "Event.h"


class HealthComponent : public dae::Component {
public:
    HealthComponent(dae::GameObject * pOwner) : Component(pOwner) {}

    // event triggered whenever health changes.
    Event<> OnHealthChanged;

    void TakeDamage();

    int GetLives() const;

private:
    int m_lives = 3;
};



