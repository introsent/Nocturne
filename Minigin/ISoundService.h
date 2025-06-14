#pragma once
#include <string>

namespace dae
{
    class ISoundService {
    public:
        virtual ~ISoundService() = default;
        virtual void RegisterSound(const std::string& id, const std::string& path) = 0;
        virtual void PlaySound(const std::string& id) = 0;
        virtual void ToggleMute() = 0; 
        virtual bool IsMuted() const = 0;
    };
}


