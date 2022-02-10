#pragma once

#include <vector>

#include "VulkanLoader.h"

class VulkanDevice;

class VulkanRHI {
public:
    VulkanRHI();

    void Init();
    void Shutdown();

private:    /* functions */
    void CreateInstance();
    // Select a GPU from avaliable GPUs
    void PickAndInitDevice();

private:    /* variables */
    VkInstance Instance;
    std::vector<const char*> InstanceLayers;
    std::vector<const char*> InstanceExtensions;
    
    // Logical device for selected GPU
    VulkanDevice* Device;
};