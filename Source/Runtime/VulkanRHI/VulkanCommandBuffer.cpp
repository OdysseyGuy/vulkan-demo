#include "VulkanCommandBuffer.h"
#include "VulkanCore.h"
#include "VulkanDevice.h"

VulkanCommandPool::VulkanCommandPool(VulkanDevice *inDevice,
                                     uint32_t      inQueueFamilyIndex)
    : device(inDevice)
    , queueFamilyIndex(inQueueFamilyIndex)
    , commandPool(VK_NULL_HANDLE)
{
}

void VulkanCommandPool::CreateCommandPool()
{
    VkCommandPoolCreateInfo cmdPoolCreateInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .queueFamilyIndex = queueFamilyIndex,
    };

    VK_CALL(vkCreateCommandPool(device->GetLogicalDeviceHandle(),
                                &cmdPoolCreateInfo, nullptr, &commandPool));
}

void VulkanCommandPool::Destroy()
{
    vkDestroyCommandPool(device->GetLogicalDeviceHandle(), commandPool,
                         nullptr);
}

VulkanCommandBuffer::VulkanCommandBuffer(VulkanDevice      *inDevice,
                                         VulkanCommandPool *inCommandPool)
    : device(inDevice)
    , commandPool(inCommandPool)
    , commandBuffer(VK_NULL_HANDLE)
{
}

void VulkanCommandBuffer::Allocate()
{
    VkCommandBufferAllocateInfo commandBufferAllocateInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = commandPool->GetHandle(),
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };

    VK_CALL(vkAllocateCommandBuffers(device->GetLogicalDeviceHandle(),
                                     &commandBufferAllocateInfo,
                                     &commandBuffer));
}

void VulkanCommandBuffer::Free()
{
    vkFreeCommandBuffers(device->GetLogicalDeviceHandle(),
                         commandPool->GetHandle(), 1, &commandBuffer);
}

void VulkanCommandBuffer::Begin()
{
    VkCommandBufferBeginInfo cmdBufBeginInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    };

    VK_CALL(vkBeginCommandBuffer(commandBuffer, &cmdBufBeginInfo));
}

void VulkanCommandBuffer::End() { VK_CALL(vkEndCommandBuffer(commandBuffer)); }

void VulkanCommandBuffer::Submit(VkQueue Queue) {}