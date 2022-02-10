#pragma once

#include <vector>

#include "VulkanLoader.h"

class VulkanDescriptorPool;

/**
 * Logical Device interface to interact with Physical device.
 */
class VulkanDevice {
public:
    VulkanDevice(VkPhysicalDevice InGpu);
    ~VulkanDevice();

    void CreateDevice();
    void WaitUntilIdle();
    void Destroy();

    VkQueue GetGraphicsQueue() { return GraphicsQueue; }
    VkQueue GetComputeQueue() { return ComputeQueue; }

    VkDevice GetLogicalDeviceHandle() { return Device; }
    VkPhysicalDeviceProperties GetGpuProps() const { return GpuProps; }

private:
    // TODO: Handle allocations in a sperate class
    void AllocateDeviceMemory(VkDeviceMemory DeviceMemory, VkMemoryAllocateFlags Flags);
    
private:    /* variables */
    VkDevice Device;

    VkPhysicalDevice            Gpu;
    VkPhysicalDeviceProperties  GpuProps;
    
    VkPhysicalDeviceMemoryProperties GpuMemoryProps;

    VkQueue GraphicsQueue;
    VkQueue ComputeQueue;

    VulkanDescriptorPool* DescriptorPool;

    std::vector<const char*> DeviceExtensions;
    std::vector<const char*> DeviceLayers;
};