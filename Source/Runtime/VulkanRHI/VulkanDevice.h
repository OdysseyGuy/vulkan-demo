#pragma once

#include <vector>

#include "VulkanLoader.h"

class VulkanDescriptorPool;

/**
 * Logical Device interface to interact with Physical device.
 */
class VulkanDevice
{
public:
    VulkanDevice(VkPhysicalDevice InGpu);
    ~VulkanDevice();

    void CreateDevice();
    void WaitUntilIdle();
    void Destroy();

    VkQueue GetGraphicsQueue() { return graphicsQueue; }
    VkQueue GetComputeQueue() { return computeQueue; }

    VkDevice                   GetLogicalDeviceHandle() { return device; }
    VkPhysicalDeviceProperties GetGpuProps() const { return gpuProps; }

private:
    // TODO: Handle allocations in a sperate class
    void AllocateDeviceMemory(VkDeviceMemory        DeviceMemory,
                              VkMemoryAllocateFlags Flags);

private:
    VkDevice device;

    VkPhysicalDevice           gpu;
    VkPhysicalDeviceProperties gpuProps;

    VkPhysicalDeviceMemoryProperties gpuMemoryProps;

    VkQueue graphicsQueue;
    VkQueue computeQueue;

    VulkanDescriptorPool *descriptorPool;

    std::vector<const char *> deviceExtensions;
    std::vector<const char *> deviceLayers;
};