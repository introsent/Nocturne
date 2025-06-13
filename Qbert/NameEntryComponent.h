#pragma once
#include <vector>
#include "TextComponent.h"
#include "GameMode.h"

class NameEntryComponent : public dae::Component {
public:
    NameEntryComponent(dae::GameObject* pOwner, GameMode gameMode);

    void SetSlotTexts(const std::vector<dae::GameObject*>& slots);
    void SetDoneText(dae::GameObject* done) { m_pDoneText = done->GetComponent<dae::TextComponent>(); }
    void SetArrow(dae::GameObject* arrow) { m_pArrow = arrow; }
    void SetWarningText(dae::GameObject* warning) { m_pWarningText = warning->GetComponent<dae::TextComponent>(); }
    void SetTitleText(dae::GameObject* title);

    void HandleUp();
    void HandleDown();
    void HandleLeft();
    void HandleRight();
    void HandleSelect();

private:
    void UpdateSlotText(int index);
    void UpdateArrowPosition();

    std::string m_characters;
    std::vector<int> m_slotIndices;
    int m_currentSelection;
    std::vector<dae::TextComponent*> m_slotTexts;
    dae::TextComponent* m_pDoneText = nullptr;
    dae::TextComponent* m_pWarningText = nullptr;
    dae::TextComponent* m_pTitleText = nullptr;
    dae::GameObject* m_pArrow = nullptr;

    GameMode m_savedGameMode;
    std::vector<std::string> m_playerNames;
    int m_requiredNames;
};