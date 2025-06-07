#include "DeadState.h"
#include "QBertPlayer.h"
#include <iostream>
#include "AnimationComponent.h"
#include "IdleState.h"
#include "Scene.h"
#include "SceneManager.h"

void DeadState::Enter(QBertPlayer*) {
    auto dialogueCloud = std::make_shared<dae::GameObject>();
    dialogueCloud->AddComponent<dae::TextureComponent>(dialogueCloud.get(), "../Data/Qbert Curses.png");
    dialogueCloud->SetParent(owner);
    dialogueCloud->SetLocalPosition(m_dialogueCloudLocalOffset);

    m_dialogueCloud = dialogueCloud;
    dae::SceneManager::GetInstance().GetActiveScene()->Add(m_dialogueCloud);

    m_deathTimer = 0.f;
}

std::unique_ptr<QBertState> DeadState::Update(QBertPlayer* player, float deltaTime) {
    m_deathTimer += deltaTime;
    if (m_deathTimer >= DEATH_DURATION) {
        player->Respawn();
        return std::make_unique<IdleState>(owner);
    }
    return nullptr;
}

void DeadState::Exit(QBertPlayer*)
{
    dae::SceneManager::GetInstance().GetActiveScene()->Remove(m_dialogueCloud);
    m_dialogueCloud.reset();
}
