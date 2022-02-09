#pragma once

#include <vulkan/vulkan.h>
#include <vector>

/**
 * Logical Device interface to interact with Physical device.
 */
class VulkanDevice {
public:
    VulkanDevice(VkPhysicalDevice InGpu);
    ~VulkanDevice();

    void CreateDevice();
    void Destroy();

    VkQueue GetGraphicsQueue() { return GraphicsQueue; }
    VkQueue GetComputeQueue() { return ComputeQueue; }

    VkDevice GetLogicalDeviceHandle() { return Device; }

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

    std::vector<const char*> DeviceExtensions;
    std::vector<const char*> DeviceLayers;
};