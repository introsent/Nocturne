#include "KillCommand.h"

#include "HealthComponent.h"

dae::KillCommand::KillCommand(GameObject* pObject) : m_pObject(pObject)
{
}

void dae::KillCommand::Execute()
{
    if (m_pObject) {
        if (auto health = m_pObject->GetComponent<HealthComponent>()) {
            health->TakeDamage();
        }
    }
}
