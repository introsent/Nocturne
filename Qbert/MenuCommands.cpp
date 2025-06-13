#include "MenuCommands.h"
#include "SceneManager.h"
#include "MenuComponent.h"
#include "Scene.h"

MenuSelectCommand::MenuSelectCommand(bool moveUp) : m_MoveUp(moveUp) {}

void MenuSelectCommand::Execute()
{
    if (auto scene = dae::SceneManager::GetInstance().GetActiveScene())
    {
        for (auto& obj : scene->GetAllObjects())
        {
            if (auto menu = obj->GetComponent<MenuComponent>())
            {
                m_MoveUp ? menu->SelectPrevious() : menu->SelectNext();
                return;
            }
        }
    }
}

void MenuActivateCommand::Execute()
{
    if (auto scene = dae::SceneManager::GetInstance().GetActiveScene())
    {
        for (auto& obj : scene->GetAllObjects())
        {
            if (auto menu = obj->GetComponent<MenuComponent>())
            {
                menu->ActivateSelected();
                return;
            }
        }
    }
}