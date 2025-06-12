#pragma once  
#include <SDL_mixer.h>  
#include <string>  

namespace dae  
{  
    struct SoundInfo {  
        std::string path;  
        Mix_Chunk* chunk = nullptr;  
    };  
}
