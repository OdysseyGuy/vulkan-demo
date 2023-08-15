
#include <iostream>

#include "Engine.h"

int main(int argc, char const *argv[])
{
#if 0
    // if (!LoadVulkanLibrary()) {
    //     std::cout << "Failed to initialize Vulkan Library!" << std::endl;
    // }

    // VulkanRHI *RHI = new VulkanRHI();
    // RHI->Init();

    // // clean up
    // RHI->Shutdown();
    // delete RHI;
    // RHI = nullptr;
#endif

    Engine *engine = new Engine();
    engine->Init("");

    while (GetIsExitRequested()) {
        engine->Tick();
    }

    return 0;
}
