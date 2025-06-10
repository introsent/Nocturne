#pragma once
#include "CoilyState.h"
#include "FallMovement.h"

class DyingCoilyState : public CoilyState {
public:
    explicit DyingCoilyState(dae::GameObject* owner);

    void Enter(Coily* coily) override;
    std::unique_ptr<CoilyState> Update(Coily* coily, float deltaTime) override;
    void Exit(Coily* coily) override;
    std::string GetName() const override { return "Dying"; }

private:
    std::unique_ptr<FallMovement> m_fallMovement;
    glm::vec3 m_fallStart {};
};
