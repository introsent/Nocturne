#pragma once
#include <string>

namespace dae
{
    class ISoundService {
    public:
        virtual ~ISoundService() = default;
        virtual void LoadSound(const std::string& id, const std::string& path) = 0;
        virtual void PlaySound(const std::string& id) = 0;
    };
}


