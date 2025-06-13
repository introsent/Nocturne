#include "HealthComponent.h"


void HealthComponent::TakeDamage()
{
    --m_lives;
    // notify all subscribers. at the same time
    OnHealthChanged();

}

int HealthComponent::GetLives() const
{
    return m_lives;
}



