#pragma once
#include "Command.h"
#include "GameObject.h"
#include <vec2.hpp>

namespace dae
{
    class MoveCommand final : public Command
    {
    public:
        MoveCommand(GameObject* pObject, float speed, const glm::vec2& direction);

        virtual ~MoveCommand() = default;

        virtual void Execute() override;

    private:
        GameObject* m_pObject;
        float m_speed;
        glm::vec2 m_direction;
    };
}
