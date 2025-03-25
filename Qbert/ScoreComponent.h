#pragma once
#include "Component.h"
#include "Event.h"

namespace dae
{
    class ScoreComponent : public Component {
    public:

        Event<int> OnScoreChanged;
        ScoreComponent(GameObject* pOwner) : Component(pOwner) {}

        void AddScore(int amount);

        int GetScore() const;

    private:
        int m_score = 0;
    };
}


