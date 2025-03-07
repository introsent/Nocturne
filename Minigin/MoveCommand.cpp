#include "MoveCommand.h"
#include "TransformComponent.h" // To access Translate
#include <vec3.hpp>

namespace dae
{
    MoveCommand::MoveCommand(GameObject* pObject, float speed, const glm::vec2& direction)
        : m_pObject(pObject)
        , m_speed(speed)
        , m_direction(direction)
    {
    }

    void MoveCommand::Execute()
    {
        if (m_pObject)
        {
            auto transform = m_pObject->GetComponent<TransformComponent>();
            if (transform)
            {
                glm::vec3 offset(m_direction, 0.f);
                transform->Translate(offset * m_speed);
            }
        }
    }
}
