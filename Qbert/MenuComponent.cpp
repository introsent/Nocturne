#include "MenuComponent.h"
#include "GameObject.h"

using namespace dae;

MenuComponent::MenuComponent(GameObject* owner) : Component(owner) {}

void MenuComponent::Update(float)
{
    if (m_pArrow && !m_MenuItems.empty() && static_cast<size_t>(m_SelectedIndex) < m_MenuItems.size())
    {
        glm::vec3 itemPos = m_MenuItems[m_SelectedIndex]->GetWorldPosition();
        m_pArrow->SetLocalPosition(glm::vec3(itemPos.x - 40.f, itemPos.y, 0.f));
    }
}

void MenuComponent::AddMenuItem(const std::string&, std::function<void()> action)
{
    m_Actions.push_back(action);
}

void MenuComponent::SelectNext()
{
    if (m_MenuItems.empty()) return;
    m_SelectedIndex = (m_SelectedIndex + 1) % m_MenuItems.size();
}

void MenuComponent::SelectPrevious()
{
    if (m_MenuItems.empty()) return;
    m_SelectedIndex = static_cast<int>((m_SelectedIndex + m_MenuItems.size() - 1) % m_MenuItems.size());
}

void MenuComponent::ActivateSelected()
{
    if (static_cast<size_t>(m_SelectedIndex) < m_Actions.size() && m_Actions[m_SelectedIndex])
    {
        m_Actions[m_SelectedIndex]();
    }
}