#include "VulkanCore.h"
#include "VulkanCommandBuffer.h"
#include "VulkanDevice.h"

VulkanCommandPool::VulkanCommandPool(VulkanDevice* InDevice, uint32_t InQueueFamilyIndex)
    : Device(InDevice)
    , QueueFamilyIndex(InQueueFamilyIndex)
    , CommandPool(VK_NULL_HANDLE)
{
}

void VulkanCommandPool::CreateCommandPool() {
    VkCommandPoolCreateInfo CmdPoolCreateInfo {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .queueFamilyIndex = QueueFamilyIndex,
    };

    VK_CALL(vkCreateCommandPool(
        Device->GetLogicalDeviceHandle(), &CmdPoolCreateInfo, nullptr, &CommandPool));
}

void VulkanCommandPool::Destroy() {
    vkDestroyCommandPool(Device->GetLogicalDeviceHandle(), CommandPool, nullptr);
}

VulkanCommandBuffer::VulkanCommandBuffer(VulkanDevice* InDevice, VulkanCommandPool* InCommandPool)
    : Device(InDevice)
    , CommandPool(InCommandPool)
    , CommandBuffer(VK_NULL_HANDLE)
{
}

void VulkanCommandBuffer::Allocate() {
    VkCommandBufferAllocateInfo CommandBufferAllocateInfo {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = CommandPool->GetHandle(),
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1,
    };

    VK_CALL(vkAllocateCommandBuffers(
        Device->GetLogicalDeviceHandle(), &CommandBufferAllocateInfo, &CommandBuffer));
}

void VulkanCommandBuffer::Free() {
    vkFreeCommandBuffers(
        Device->GetLogicalDeviceHandle(), CommandPool->GetHandle(), 1, &CommandBuffer);
}

void VulkanCommandBuffer::Begin() {
    VkCommandBufferBeginInfo CmdBufBeginInfo {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    };

    VK_CALL(vkBeginCommandBuffer(CommandBuffer, &CmdBufBeginInfo));
}

void VulkanCommandBuffer::End() {
    VK_CALL(vkEndCommandBuffer(CommandBuffer));
}

void VulkanCommandBuffer::Submit(VkQueue Queue) {

}