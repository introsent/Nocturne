#include "TestSoundCommand.h"
#include "SoundServiceLocator.h"

using namespace dae;

void TestSoundCommand::Execute()
{
	auto* soundService = SoundServiceLocator::GetService();
	if (soundService) {
		soundService->PlaySound("test");  // Works now
	}
}

