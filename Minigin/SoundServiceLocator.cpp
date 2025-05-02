#include "SoundServiceLocator.h"

#include "NullSoundService.h"

namespace dae
{
    std::unique_ptr<ISoundService> SoundServiceLocator::m_service = std::make_unique<NullSoundService>();

    ISoundService* SoundServiceLocator::GetService() {
        return m_service.get();
    }

	void SoundServiceLocator::Register(std::unique_ptr<ISoundService> service) {
        if (service) {
            // If the service is not null, we replace the current service
            m_service = std::move(service);
        }
    }
}

