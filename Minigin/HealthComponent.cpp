#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* owner, int lives) : Component(owner), m_lives(lives) 
{
}

void dae::HealthComponent::TakeDamage()
{
    if (--m_lives <= 0) {
        std::cout << "Player died!" << std::endl;
        NotifyObservers("PlayerDied");
    }
}

int dae::HealthComponent::GetLives() const
{
    return m_lives;
}



