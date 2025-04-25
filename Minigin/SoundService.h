#pragma once
#include "ISoundService.h"
#include <memory>

namespace dae
{
    class SoundService : public ISoundService {
    public:
        SoundService();
        ~SoundService() override;

        void LoadSound(const std::string& id, const std::string& path) override;
        void PlaySound(const std::string& id) override;

    private:
        class MixerImpl;
        std::unique_ptr<MixerImpl> m_mixerPimpl;
    };
}
