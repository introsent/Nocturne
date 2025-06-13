#pragma once
#include "Command.h"


class MenuSelectCommand : public dae::Command
{
public:
    explicit MenuSelectCommand(bool moveUp);
    void Execute() override;
private:
    bool m_MoveUp;
};

class MenuActivateCommand : public dae::Command
{
public:
    MenuActivateCommand() = default;
    void Execute() override;
};
