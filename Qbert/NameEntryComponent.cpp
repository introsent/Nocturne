#include "NameEntryComponent.h"
#include <algorithm>
#include "SceneManager.h"
#include "Scene.h"
#include "HighscoreLoader.h"

NameEntryComponent::NameEntryComponent(dae::GameObject* pOwner)
    : Component(pOwner) {
    m_characters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    m_slotIndices = std::vector<int>(5, 0); // All spaces initially
    m_currentSelection = 0;
}

void NameEntryComponent::UpdateSlotText(int index)
{
	m_slotTexts[index]->SetText(std::string(1, m_characters[m_slotIndices[index]]));
}

void NameEntryComponent::UpdateArrowPosition()
{
	float x = static_cast<float>(180 + m_currentSelection * 50);
	float y = static_cast<float>((m_currentSelection < 5) ? 200 : 250);
	m_pArrow->SetLocalPosition(glm::vec3(x, y, 0));
}

void NameEntryComponent::HandleSelect()
{
    if (m_currentSelection == 5) { // "Done" selected
        std::string name;
        for (int i = 0; i < 5; ++i) {
            name += m_characters[m_slotIndices[i]];
        }
        // Trim trailing spaces
        while (!name.empty() && name.back() == ' ') name.pop_back();
        if (name.empty()) name = "ANON";

        // Check for duplicate name
        auto scores = HighscoreLoader::ReadHighScores();
        bool nameExists = std::any_of(scores.begin(), scores.end(), [&name](const auto& entry) {
            return entry.first == name;
            });
        if (nameExists && m_pWarningText) {
            m_pWarningText->SetText("Player with that name exists");
        }
        else {
            if (m_pWarningText) m_pWarningText->SetText("");
            SceneManager::CreateGameScene(name);
            dae::SceneManager::GetInstance().SetActiveScene("Main");
        }
    }
}

void NameEntryComponent::SetSlotTexts(const std::vector<dae::GameObject*>& slots)
{
    m_slotTexts.clear();
    for (auto* go : slots) {
        m_slotTexts.push_back(go->GetComponent<dae::TextComponent>());
    }
}

void NameEntryComponent::HandleUp()
{
    if (m_currentSelection < 5) {
        m_slotIndices[m_currentSelection] = (m_slotIndices[m_currentSelection] + 1) % 27;
        UpdateSlotText(m_currentSelection);
    }
}

void NameEntryComponent::HandleDown()
{
    if (m_currentSelection < 5) {
        m_slotIndices[m_currentSelection] = (m_slotIndices[m_currentSelection] - 1 + 27) % 27;
        UpdateSlotText(m_currentSelection);
    }
}

void NameEntryComponent::HandleLeft()
{
    m_currentSelection = (m_currentSelection - 1 + 6) % 6;
    UpdateArrowPosition();
}

void NameEntryComponent::HandleRight()
{
    m_currentSelection = (m_currentSelection + 1) % 6;
    UpdateArrowPosition();
}


