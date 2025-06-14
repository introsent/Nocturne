#include "NameEntryComponent.h"
#include <algorithm>
#include <string>
#include "SceneManager.h"
#include "Scene.h"
#include "HighscoreLoader.h"

NameEntryComponent::NameEntryComponent(dae::GameObject* pOwner, GameMode gameMode)
    : Component(pOwner), m_savedGameMode(gameMode) {
    m_characters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    m_slotIndices = std::vector<int>(5, 0); // All spaces initially
    m_currentSelection = 0;
    if (gameMode == GameMode::Solo) {
        m_requiredNames = 1;
    }
    else { // Co-op or Versus
        m_requiredNames = 2;
    }
}

void NameEntryComponent::SetTitleText(dae::GameObject* title) {
    m_pTitleText = title->GetComponent<dae::TextComponent>();
    if (m_pTitleText) {
        if (m_requiredNames == 1) {
            m_pTitleText->SetText("Enter Your Name");
        }
        else {
            m_pTitleText->SetText("Enter Player 1's Name");
        }
    }
}

void NameEntryComponent::UpdateSlotText(int index) {
    m_slotTexts[index]->SetText(std::string(1, m_characters[m_slotIndices[index]]));
}

void NameEntryComponent::UpdateArrowPosition() {
    float x = static_cast<float>(180 + m_currentSelection * 50);
    float y = static_cast<float>((m_currentSelection < 5) ? 200 : 250);
    m_pArrow->SetLocalPosition(glm::vec3(x, y, 0));
}

void NameEntryComponent::HandleSelect() {
    if (m_currentSelection == 5) { // "Done" selected
        std::string name;
        for (int i = 0; i < 5; ++i) {
            name += m_characters[m_slotIndices[i]];
        }
        // Trim trailing spaces
        while (!name.empty() && name.back() == ' ') name.pop_back();
        if (name.empty()) name = "ANON";

        // Check for duplicate name
        auto scores = HighscoreLoader::ReadHighScores(m_savedGameMode);
        bool nameExists = std::any_of(scores.begin(), scores.end(), [&name](const auto& entry) {
            return entry.first == name;
            });
        if (nameExists) {
            if (m_pWarningText) m_pWarningText->SetText("Player with that name exists");
        }
        else {
            if (m_pWarningText) m_pWarningText->SetText(" ");
            m_playerNames.push_back(name);
            if (m_playerNames.size() == static_cast<size_t>(m_requiredNames)) {
                SceneManager::CreateGameScene(m_savedGameMode, m_playerNames);
                dae::SceneManager::GetInstance().SetActiveScene("Main");
            }
            else {
                // Reset slots for next player
                m_slotIndices = std::vector<int>(5, 0);
                for (int i = 0; i < 5; ++i) {
                    UpdateSlotText(i);
                }
                m_currentSelection = 0;
                UpdateArrowPosition();
                if (m_pTitleText) {
                    m_pTitleText->SetText("Enter Player " + std::to_string(m_playerNames.size() + 1) + "'s Name");
                }
            }
        }
    }
}

void NameEntryComponent::SetSlotTexts(const std::vector<dae::GameObject*>& slots) {
    m_slotTexts.clear();
    for (auto* go : slots) {
        m_slotTexts.push_back(go->GetComponent<dae::TextComponent>());
    }
}

void NameEntryComponent::HandleUp() {
    if (m_currentSelection < 5) {
        m_slotIndices[m_currentSelection] = (m_slotIndices[m_currentSelection] + 1) % 27;
        UpdateSlotText(m_currentSelection);
    }
}

void NameEntryComponent::HandleDown() {
    if (m_currentSelection < 5) {
        m_slotIndices[m_currentSelection] = (m_slotIndices[m_currentSelection] - 1 + 27) % 27;
        UpdateSlotText(m_currentSelection);
    }
}

void NameEntryComponent::HandleLeft() {
    m_currentSelection = (m_currentSelection - 1 + 6) % 6;
    UpdateArrowPosition();
}

void NameEntryComponent::HandleRight() {
    m_currentSelection = (m_currentSelection + 1) % 6;
    UpdateArrowPosition();
}