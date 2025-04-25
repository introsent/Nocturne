#pragma once
#include "Command.h"

namespace dae
{
    class TestSoundCommand final : public Command
    {
    public:
        TestSoundCommand() = default;
        ~TestSoundCommand() override = default;
        TestSoundCommand(const TestSoundCommand&) = delete;
        TestSoundCommand& operator=(const TestSoundCommand&) = delete;
        TestSoundCommand(TestSoundCommand&&) noexcept = delete;
        TestSoundCommand& operator=(TestSoundCommand&&) noexcept = delete;

        void Execute() override;
    };
}



