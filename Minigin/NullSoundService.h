#pragma once
#include "ISoundService.h"

namespace dae
{
    // Internal null object implementation
    class NullSoundService final : public ISoundService
    {
    public:
        void LoadSound(const std::string&, const std::string&) override {}
        void PlaySound(const std::string&) override {}
    };
};

