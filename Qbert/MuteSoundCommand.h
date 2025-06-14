#pragma once
#include "Command.h"
#include "SoundServiceLocator.h"

class MuteSoundCommand final : public dae::Command {
public:
    void Execute() override {
        auto soundService = dae::SoundServiceLocator::GetService();
        if (soundService) {
            soundService->ToggleMute();
        }
    }
};