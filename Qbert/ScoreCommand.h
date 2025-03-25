#pragma once
#include "Command.h"
#include "GameObject.h"

namespace dae
{
    class ScoreCommand final : public Command
    {
    public:
        ScoreCommand(GameObject* pObject, int scoreAmount);
        ~ScoreCommand() override = default;
        ScoreCommand(const ScoreCommand&) = delete;
        ScoreCommand& operator=(const ScoreCommand&) = delete;
        ScoreCommand(ScoreCommand&&) noexcept = delete;
        ScoreCommand& operator=(ScoreCommand&&) noexcept = delete;

        void Execute() override;

    private:
        int m_scoreAmount;
        GameObject* m_pObject;
    };
}




