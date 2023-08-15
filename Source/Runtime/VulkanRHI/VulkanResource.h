#pragma once

#include "VulkanLoader.h"

class VulkanDevice;

class VulkanBuffer
{
public:
    VulkanBuffer(VulkanDevice *Device, uint32_t Size, VkBufferUsageFlags UsageFlags);

private:
    // Creates a buffer and allocates memory for it
    void CreateBuffer();

private:
    VulkanDevice *device;

    VkBuffer handle;

    // Device memory allocation for this buffer
    VkDeviceMemory deviceMemory;

    uint32_t size;                 // Buffer allocation size
    VkBufferUsageFlags usageFlags; // Usage flags for device memory allocation
};

/*
 * https://arm-software.github.io/vulkan_best_practice_for_mobile_developers/samples/performance
 * layout_transitions/layout_transitions_tutorial.html
 */

class VulkanImage
{
public:
    VulkanImage(VulkanDevice *device, uint32_t width, uint32_t height);

private:
    void CreateImage();

private:
    VulkanDevice *device;

    uint32_t width, height;

    VkImage handle;
    VkImageView view;

    // Device memory allocation
    VkDeviceMemory deviceMemory;

    VkImageLayout layout;
};
