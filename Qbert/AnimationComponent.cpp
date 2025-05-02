// AnimationComponent.cpp
#include "AnimationComponent.h"
#include "TextureComponent.h"

using namespace dae;

AnimationComponent::AnimationComponent(GameObject* pOwner,
    TextureComponent* texComp,
    glm::vec2 frameSize,
    int numFrames,
    float frameDuration)
    : Component(pOwner)
    , m_pTex(texComp)
    , m_frameSize(frameSize)
    , m_numFrames(numFrames)
    , m_frameDuration(frameDuration)
{
}

void AnimationComponent::Update(float dt) {
    m_accTime += dt;
    if (m_accTime >= m_frameDuration) {
        m_accTime -= m_frameDuration;
        m_currentFrame = (m_currentFrame + 1) % m_numFrames;
    
        m_pTex->SetSrcRect({
          static_cast<float>(m_currentFrame)* m_frameSize.x, 0,
          m_frameSize.x, m_frameSize.y
            });
    }
}

void AnimationComponent::SetFrame(int frameIndex) {
    m_currentFrame = frameIndex % m_numFrames;
    m_pTex->SetSrcRect({
      static_cast<float>(m_currentFrame) * m_frameSize.x, 0,
      m_frameSize.x, m_frameSize.y
        });
}
