#pragma once
#include "Command.h"
#include <SDL_mixer.h>
#include <unordered_map>
#include <string>
#include <mutex>

namespace dae
{
    struct SoundInfo;

    class LoadSoundCommand : public Command {
        std::string m_id;
        std::unordered_map<std::string, SoundInfo>& m_soundInfo;
        std::mutex& m_soundMutex;

    public:
        LoadSoundCommand(std::string id,
            std::unordered_map<std::string, SoundInfo>& soundInfo,
            std::mutex& mutex);

        void Execute() override;
    };
}