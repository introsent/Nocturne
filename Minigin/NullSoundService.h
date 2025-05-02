#pragma once
#include "ISoundService.h"

namespace dae
{
    // Internal null object implementation
    class NullSoundService final : public ISoundService
    {
    public:
        void LoadSound(const std::string& id, const std::string& path) override {}
        void PlaySound(const std::string& id) override {}
    };
};

