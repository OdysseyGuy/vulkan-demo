#include "VulkanCore.h"
#include "VulkanResource.h"
#include "VulkanDevice.h"

VulkanBuffer::VulkanBuffer(VulkanDevice* InDevice, uint32_t InSize, VkBufferUsageFlags InFlags)
    : Device(InDevice)
    , BufferHandle(VK_NULL_HANDLE)
    , DeviceMemory(VK_NULL_HANDLE)
    , Size(InSize)
    , UsageFlags(InFlags)
{
}

void VulkanBuffer::CreateBuffer() {
    // Create vulkan buffer
    VkBufferCreateInfo BufferCreateInfo {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = Size,
        .usage = UsageFlags,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VK_CALL(vkCreateBuffer(
        Device->GetLogicalDeviceHandle(), &BufferCreateInfo, nullptr, &BufferHandle));

    // Allocate memory for the buffer

    // Memory requriments for image allocation
    VkMemoryRequirements MemoryRequirements;
    vkGetBufferMemoryRequirements(
        Device->GetLogicalDeviceHandle(), BufferHandle, &MemoryRequirements);
}

VulkanImage::VulkanImage(VulkanDevice* InDevice, uint32_t InWidth, uint32_t InHeight)
    : Device(InDevice)
    , Width(InWidth)
    , Height(InHeight)
    , ImageHandle(VK_NULL_HANDLE)
{
}

void VulkanImage::CreateImage() {
    // TODO: Check if image is in right layout

    VkImageCreateInfo ImageCreateInfo {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED  // No purpose specific
    };

    VK_CALL(vkCreateImage(
        Device->GetLogicalDeviceHandle(), &ImageCreateInfo, nullptr, &ImageHandle));

    // Memory requriments for image allocation
    VkMemoryRequirements MemoryRequirements;
    vkGetImageMemoryRequirements(
        Device->GetLogicalDeviceHandle(), ImageHandle, &MemoryRequirements);

    VkMemoryAllocateInfo AllocateInfo {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    };

    // Allocate actual device memory for the image
    // TODO: Handle this in Device class in future
    vkAllocateMemory(Device->GetLogicalDeviceHandle(), &AllocateInfo, nullptr, &DeviceMemory);

    // Bind the allocated Device Memory with Vulkan Image Object
}