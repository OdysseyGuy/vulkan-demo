#include "VulkanLoader.h"

#include <vector>
#include <iostream>

#include "VulkanRHI.h"
#include "VulkanCore.h"

int main(int argc, char const *argv[]) {
    if (!LoadVulkanLibrary()) {
        std::cout << "Failed to initialize Vulkan Library!" << std::endl;
    }

    VulkanRHI *RHI = new VulkanRHI();
    RHI->Init();
    RHI->Shutdown();
    
    delete RHI;

    return 0;
}