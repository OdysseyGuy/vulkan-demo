#pragma once

#include "VulkanLoader.h"

class VulkanDevice;

class VulkanCommandPool
{
public:
    VulkanCommandPool(VulkanDevice *Device, uint32_t QueueFamilyIndex);

    void CreateCommandPool();
    void Destroy();

    VkCommandPool GetHandle() { return commandPool; }

private:
    VulkanDevice *device;

    // Queue this command pool belongs to
    uint32_t queueFamilyIndex;

    VkCommandPool commandPool;
};

class VulkanCommandBuffer
{
public:
    VulkanCommandBuffer(VulkanDevice *Device, VulkanCommandPool *CmdPool);

    // Memory allocations
    void Allocate();
    void Free();

    // Command Buffer Recording
    void Begin();
    void End();

    // Submit command buffer to a Queue
    void Submit(VkQueue Queue);

    VkCommandBuffer GetHandle() { return commandBuffer; }

private:
    VulkanDevice      *device;
    VulkanCommandPool *commandPool;

    VkCommandBuffer commandBuffer;
};