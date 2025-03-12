#include "HealthComponent.h"


void dae::HealthComponent::TakeDamage()
{
    --m_lives;
    NotifyObservers(Event::PlayerDied, this);
}

int dae::HealthComponent::GetLives() const
{
    return m_lives;
}



