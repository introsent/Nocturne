#pragma once
#include "Command.h"
#include <SDL_mixer.h>
#include <unordered_map>
#include <string>

namespace dae
{
    class LoadSoundCommand : public Command {
        std::string m_id;
        std::string m_path;
        std::unordered_map<std::string, Mix_Chunk*>& m_soundMap;

    public:
        LoadSoundCommand(std::string id, std::string path,
            std::unordered_map<std::string, Mix_Chunk*>& soundMap);

        void Execute() override;
    };
}
