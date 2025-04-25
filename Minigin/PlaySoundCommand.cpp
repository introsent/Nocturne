#include "PlaySoundCommand.h"

dae::PlaySoundCommand::PlaySoundCommand(std::string id, std::unordered_map<std::string, Mix_Chunk*>& soundMap) : 
	m_id(std::move(id)), 
	m_soundMap(soundMap)
{
}

void dae::PlaySoundCommand::Execute()
{
	if (auto it = m_soundMap.find(m_id); it != m_soundMap.end()) {
		Mix_PlayChannel(-1, it->second, 0);
	}
}
