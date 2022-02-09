#pragma once

#include <vulkan/vulkan.h>

class VulkanDevice;

class VulkanCommandPool {
public:
    VulkanCommandPool(VulkanDevice* Device, uint32_t QueueFamilyIndex);

    void CreateCommandPool();
    void Destroy();

    VkCommandPool GetHandle() {
        return CommandPool;
    }

private:
    VulkanDevice*   Device;

    // Queue this command pool belongs to
    uint32_t        QueueFamilyIndex;

    VkCommandPool   CommandPool;
};

class VulkanCommandBuffer {
public:
    VulkanCommandBuffer(VulkanDevice* Device, VulkanCommandPool* CmdPool);

    // Memory allocations
    void Allocate();
    void Free();

    // Command Buffer Recording
    void Begin();
    void End();

    // Submit command buffer to a Queue
    void Submit(VkQueue Queue);

    VkCommandBuffer GetHandle() {
        return CommandBuffer;
    }

private:
    VulkanDevice*       Device;
    VulkanCommandPool*  CommandPool;

    VkCommandBuffer     CommandBuffer;
};