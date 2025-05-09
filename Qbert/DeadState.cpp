#include "DeadState.h"
#include "QBertPlayer.h"
#include <iostream>

#include "AnimationComponent.h"
#include "IdleState.h"
#include "Scene.h"
#include "SceneManager.h"

// Dead State
void DeadState::Enter(dae::GameObject* player) {
    auto dialogueCloud = std::make_shared<dae::GameObject>();
    dialogueCloud->AddComponent<dae::TextureComponent>(dialogueCloud.get(), "../Data/Qbert Curses.png");
    dialogueCloud->SetParent(player);
    dialogueCloud->SetLocalPosition(glm::vec3(10.f, -32.f, 0.f));

    m_DialogueCloud = dialogueCloud;
    dae::SceneManager::GetInstance().GetActiveScene()->Add(m_DialogueCloud);

    m_DeathTimer = 0.f;
}

void DeadState::Update(dae::GameObject* player, float deltaTime) {
    m_DeathTimer += deltaTime;
    if (m_DeathTimer >= DEATH_DURATION) {
        QBertPlayer* qbertPlayer = player->GetComponent<QBertPlayer>();
        qbertPlayer->Respawn();
        qbertPlayer->ChangeState(std::make_unique<IdleState>());
    }
}

void DeadState::Exit(dae::GameObject*)
{
    dae::SceneManager::GetInstance().GetActiveScene()->Remove(m_DialogueCloud);
    m_DialogueCloud.reset();
}
