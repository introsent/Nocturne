#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* owner, int lives) : Component(owner), m_lives(lives) 
{
}

void dae::HealthComponent::TakeDamage()
{
    --m_lives;
	NotifyObservers(Event::PlayerDied);
}

int dae::HealthComponent::GetLives() const
{
    return m_lives;
}



