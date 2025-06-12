#include "PlaySoundCommand.h"
#include <SDL_mixer.h>
#include "SoundInfo.h"

namespace dae
{
    PlaySoundCommand::PlaySoundCommand(std::string id,
        std::unordered_map<std::string, struct SoundInfo>& soundInfo,
        std::mutex& mutex)
        : m_id(std::move(id))
        , m_soundInfo(soundInfo)
        , m_soundMutex(mutex)
    {
    }

    void PlaySoundCommand::Execute()
    {
        std::unique_lock lock(m_soundMutex);

        auto it = m_soundInfo.find(m_id);
        if (it == m_soundInfo.end()) return; // Not registered

        SoundInfo & info = it->second;

        // Load sound if missing
        if (!info.chunk) {
            info.chunk = Mix_LoadWAV(info.path.c_str());
            if (!info.chunk) return; // Handle error
        }

        // Unlock while playing to avoid blocking
        lock.unlock();
        Mix_PlayChannel(-1, info.chunk, 0);
    }
}