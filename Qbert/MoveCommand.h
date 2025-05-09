#pragma once
#include "Command.h"
#include "GameObject.h"

class MoveCommand : public dae::Command {
public:
    MoveCommand(dae::GameObject* pObject, const glm::ivec2& direction);
    void Execute() override;

private:
    dae::GameObject* m_pPlayer;
    glm::ivec2 m_Direction;
};
