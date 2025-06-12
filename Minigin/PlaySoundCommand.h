#pragma once
#include "Command.h"
#include <SDL_mixer.h>
#include <unordered_map>
#include <string>
#include <mutex>

namespace dae
{
    class PlaySoundCommand : public Command {
        std::string m_id;
        std::unordered_map<std::string, struct SoundInfo>& m_soundInfo;
        std::mutex& m_soundMutex;

    public:
        PlaySoundCommand(std::string id,
            std::unordered_map<std::string, struct SoundInfo>& soundInfo,
            std::mutex& mutex);

        void Execute() override;
    };
}