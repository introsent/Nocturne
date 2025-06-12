#include "LoadSoundCommand.h"
#include <SDL_mixer.h>
#include "SoundInfo.h"
#include <iostream>
namespace dae
{
    LoadSoundCommand::LoadSoundCommand(std::string id,
        std::unordered_map<std::string, SoundInfo>& soundInfo,
        std::mutex& mutex)
        : m_id(std::move(id))
        , m_soundInfo(soundInfo)
        , m_soundMutex(mutex)
    {
    }

    void LoadSoundCommand::Execute()
    {
        std::lock_guard lock(m_soundMutex);

        auto it = m_soundInfo.find(m_id);
        if (it == m_soundInfo.end() || it->second.chunk) return;

        it->second.chunk = Mix_LoadWAV(it->second.path.c_str());

        std::cout << it->first << std::endl;
    }
}