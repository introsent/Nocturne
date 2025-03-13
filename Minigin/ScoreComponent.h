#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
    class ScoreComponent : public Component, public Subject {
    public:
        ScoreComponent(GameObject* pOwner) : Component(pOwner) {}

        void AddScore(int amount);

        int GetScore() const;

    private:
        int m_score = 0;
    };
}


