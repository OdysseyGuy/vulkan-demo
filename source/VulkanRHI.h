#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class VulkanDevice;

class VulkanRHI {
public:
    VulkanRHI();

    void Shutdown();

private:    /* functions */
    void CreateInstance();
    // Select a GPU from avaliable GPUs
    void PickAndInitGpu();

private:    /* variables */
    VkInstance Instance;
    std::vector<const char*> InstanceLayers;
    std::vector<const char*> InstanceExtensions;
    
    // Logical device for selected GPU
    VulkanDevice* Device;
};