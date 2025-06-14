#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include "SceneManager.h"
#include <filesystem>


int main(int, char* []) {
    std::cout << "Working dir: " << std::filesystem::current_path() << std::endl;
    dae::Minigin engine("Data/");
    SceneManager::CreateMenuScene();
    engine.Run();

    return 0;
}


