#include "AnimationComponent.h"
#include "TextureComponent.h"

using namespace dae;

AnimationComponent::AnimationComponent(GameObject* pOwner,
    TextureComponent* texComp,
    glm::vec2 frameSize,
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
{
}

void AnimationComponent::Update(float) {

    //TODO: FOR ENEMIES FUTURE IMPLEMENTATION
    //m_accTime += dt;
    //if (m_accTime >= m_frameDuration) {
    //    m_accTime -= m_frameDuration;
    //    m_currentFrame = (m_currentFrame + 1) % m_numFrames;
    //
    //    m_pTex->SetSrcRect({
    //      static_cast<float>(m_currentFrame)* m_frameSize.x, 0,
    //      m_frameSize.x, m_frameSize.y
    //        });
    //}
}

void AnimationComponent::SetFrame(int frameIndex) {
    // Calculate column and row in the atlas
    m_currentCol = frameIndex % m_maxCols; // 6 columns per row
    m_currentRow = frameIndex / m_maxCols;    // Color state (0=blue, 1=yellow, 2=red)

    m_pTex->SetSrcRect({
         static_cast<float>(m_currentCol) * m_frameSize.x,
    	 static_cast<float>(m_currentRow)* m_frameSize.y,
         m_frameSize.x,
         m_frameSize.y
        });
}
