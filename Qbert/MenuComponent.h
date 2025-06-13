#pragma once
#include "Component.h"
#include <vector>
#include <functional>
#include <string>


class MenuComponent : public dae::Component
{
public:
    MenuComponent(dae::GameObject* owner);
    void Update(float deltaTime) override;

    void AddMenuItem(const std::string& text, std::function<void()> action);
    void SelectNext();
    void SelectPrevious();
    void ActivateSelected();

    void SetArrow(dae::GameObject* arrow) { m_pArrow = arrow; }
    void SetMenuItems(const std::vector<dae::GameObject*>& items) { m_MenuItems = items; }

private:
    int m_SelectedIndex = 0;
    std::vector<dae::GameObject*> m_MenuItems;
    dae::GameObject* m_pArrow = nullptr;
    std::vector<std::function<void()>> m_Actions;
};
