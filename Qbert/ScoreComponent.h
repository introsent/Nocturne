#pragma once
#include "Component.h"
#include "Event.h"


class ScoreComponent : public dae::Component {
public:

    Event<int> OnScoreChanged;
    ScoreComponent(dae::GameObject* pOwner) : Component(pOwner) {}

    void AddScore(int amount);

    int GetScore() const;

private:
    int m_score = 0;
};



