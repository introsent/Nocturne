#include "AnimationComponent.h"
#include "TextureComponent.h"

using namespace dae;

AnimationComponent::AnimationComponent(GameObject* pOwner,
    TextureComponent* texComp,
    glm::ivec2 frameSize,
    int numFrames,
    float frameDuration,
    int rows,
    int cols)
    : Component(pOwner)
    , m_pTex(texComp)
    , m_frameSize(frameSize)
    , m_numFrames(numFrames)
    , m_frameDuration(frameDuration)
    , m_maxRows(rows)
    , m_maxCols(cols)
    , m_loopStart(0)
    , m_loopEnd(numFrames - 1)
{
}

void AnimationComponent::Update(float deltaTime) {
    if (!m_autoAdvance) return;

    m_accTime += deltaTime;
    if (m_accTime >= m_frameDuration) {
        m_accTime -= m_frameDuration;
        // advance and wrap within loop range
        m_currentFrame++;
        if (m_currentFrame > m_loopEnd) {
            m_currentFrame = m_loopStart;
        }
        // apply to texture
        int col = m_currentFrame % m_maxCols;
        int row = m_currentFrame / m_maxCols;
        m_pTex->SetSrcRect({
            static_cast<float>(col) * m_frameSize.x,
            static_cast<float>(row) * m_frameSize.y,
            static_cast<float>(m_frameSize.x),
            static_cast<float>(m_frameSize.y)
            });
    }
}

void AnimationComponent::SetFrame(int frameIndex) {
    m_currentFrame = frameIndex;
    // calculate column and row in atlas
    int col = frameIndex % m_maxCols;
    int row = frameIndex / m_maxCols;
    m_pTex->SetSrcRect({
         static_cast<float>(col) * m_frameSize.x,
         static_cast<float>(row) * m_frameSize.y,
         static_cast<float>(m_frameSize.x),
         static_cast<float>(m_frameSize.y)
        });
}

void AnimationComponent::SetLoopRange(int startFrame, int endFrame) {
    m_loopStart = glm::clamp(startFrame, 0, m_numFrames - 1);
    m_loopEnd = glm::clamp(endFrame, m_loopStart, m_numFrames - 1);
    // ensure current frame is within new loop
    if (m_currentFrame < m_loopStart || m_currentFrame > m_loopEnd) {
        m_currentFrame = m_loopStart;
        SetFrame(m_currentFrame);
    }
}

void AnimationComponent::SetAutoAdvance(bool enable) {
    m_autoAdvance = enable;
}