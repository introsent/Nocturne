#include "HealthComponent.h"


void dae::HealthComponent::TakeDamage()
{
    --m_lives;
    // notify all subscribers. at the same time
    OnHealthChanged();

}

int dae::HealthComponent::GetLives() const
{
    return m_lives;
}



