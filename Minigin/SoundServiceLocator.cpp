#include "SoundServiceLocator.h"

namespace dae
{
    std::unique_ptr<ISoundService> SoundServiceLocator::m_service = nullptr;

    ISoundService* SoundServiceLocator::GetService() {
        return m_service.get();
    }

    void SoundServiceLocator::Register(std::unique_ptr<ISoundService> service) {
        m_service = std::move(service);
    }
}

