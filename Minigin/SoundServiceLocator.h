#pragma once
#include <memory>
#include "SoundService.h"

namespace dae
{
    class SoundServiceLocator {
    public:
        static ISoundService* GetService();
        static void Register(std::unique_ptr<ISoundService> service);

    private:
        static std::unique_ptr<ISoundService> m_service;
    };
}

