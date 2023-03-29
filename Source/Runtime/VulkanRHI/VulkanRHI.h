#pragma once

#include <vector>

#include "VulkanLoader.h"

class VulkanDevice;

class VulkanRHI
{
public:
    VulkanRHI();

    void Init();
    void Shutdown();

private:
    void CreateInstance();
    // Select a GPU from avaliable GPUs
    void PickAndInitDevice();

private:
    VkInstance                instance;
    std::vector<const char *> instanceLayers;
    std::vector<const char *> instanceExtensions;

    // Logical device for selected GPU
    VulkanDevice *device;
};