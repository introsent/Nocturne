#include "TestSoundCommand.h"
//#include <iostream>
#include "SoundServiceLocator.h"

using namespace dae;

void TestSoundCommand::Execute()
{
	if (auto* soundService = SoundServiceLocator::GetService()) {
		soundService->PlaySound("test");  
	}

	//	to test threading only
	//td::cout << "Main thread continues after PlaySound...\n";
	//or (int i = 0; i < 10000000; ++i) {
	//	volatile double result = sqrt(i) * tan(i);
	//	std::cout << result << "\n"; 
	//
	//td::cout << "Main thread finished heavy work\n";
}

