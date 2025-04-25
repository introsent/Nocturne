#pragma once
#include "Command.h"
#include <SDL_mixer.h>
#include <unordered_map>
#include <string>

namespace dae
{
    class PlaySoundCommand : public Command {
        std::string m_id;
        std::unordered_map<std::string, Mix_Chunk*>& m_soundMap;

    public:
        PlaySoundCommand(std::string id,
            std::unordered_map<std::string, Mix_Chunk*>& soundMap);

        void Execute() override;
    };
}

