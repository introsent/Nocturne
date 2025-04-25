#include "LoadSoundCommand.h"

dae::LoadSoundCommand::LoadSoundCommand(std::string id, std::string path, std::unordered_map<std::string, Mix_Chunk*>& soundMap) :
	m_id(std::move(id)),
	m_path(std::move(path)),
	m_soundMap(soundMap)
{
}

void dae::LoadSoundCommand::Execute()
{
	if (Mix_Chunk* sound = Mix_LoadWAV(m_path.c_str())) {
		m_soundMap[m_id] = sound;
	}
}
