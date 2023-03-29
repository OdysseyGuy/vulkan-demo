#include "VulkanResource.h"
#include "VulkanCore.h"
#include "VulkanDevice.h"

VulkanBuffer::VulkanBuffer(VulkanDevice *inDevice, uint32_t inSize,
                           VkBufferUsageFlags inFlags)
    : device(inDevice)
    , handle(VK_NULL_HANDLE)
    , deviceMemory(VK_NULL_HANDLE)
    , size(inSize)
    , usageFlags(inFlags)
{
}

void VulkanBuffer::CreateBuffer()
{
    // Create vulkan buffer
    VkBufferCreateInfo bufferCreateInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = size,
        .usage = usageFlags,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VK_CALL(vkCreateBuffer(device->GetLogicalDeviceHandle(), &bufferCreateInfo,
                           nullptr, &handle));

    // Allocate memory for the buffer

    // Memory requriments for image allocation
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device->GetLogicalDeviceHandle(), handle,
                                  &memoryRequirements);
}

VulkanImage::VulkanImage(VulkanDevice *inDevice, uint32_t inWidth,
                         uint32_t inHeight)
    : device(inDevice)
    , width(inWidth)
    , height(inHeight)
    , handle(VK_NULL_HANDLE)
{
}

void VulkanImage::CreateImage()
{
    // TODO: Check if image is in right layout

    VkImageCreateInfo imageCreateInfo{
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED // No purpose specific
    };

    VK_CALL(vkCreateImage(device->GetLogicalDeviceHandle(), &imageCreateInfo,
                          nullptr, &handle));

    // Memory requriments for image allocation
    VkMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements(device->GetLogicalDeviceHandle(), handle,
                                 &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo{
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    };

    // Allocate actual device memory for the image
    // TODO: Handle this in Device class in future
    vkAllocateMemory(device->GetLogicalDeviceHandle(), &allocateInfo, nullptr,
                     &deviceMemory);

    // Bind the allocated Device Memory with Vulkan Image Object
}