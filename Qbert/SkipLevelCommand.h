#pragma once
#include "Command.h"
#include "LevelManagerComponent.h"

class SkipLevelCommand final : public dae::Command {
public:
    explicit SkipLevelCommand(LevelManagerComponent* levelManager)
        : m_pLevelManager(levelManager) {
    }

    void Execute() override {
        if (m_pLevelManager) {
            m_pLevelManager->SkipLevel();
        }
    }

private:
    LevelManagerComponent* m_pLevelManager;
};
