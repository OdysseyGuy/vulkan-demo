#include "VulkanLoader.h"

#include <iostream>
#include <vector>

#include "VulkanCore.h"
#include "VulkanRHI.h"

int main(int argc, char const *argv[])
{
    if (!LoadVulkanLibrary()) {
        std::cout << "Failed to initialize Vulkan Library!" << std::endl;
    }

    VulkanRHI *RHI = new VulkanRHI();
    RHI->Init();

    // clean up
    RHI->Shutdown();
    delete RHI;

    return 0;
}