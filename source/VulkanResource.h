#pragma once

#include <vulkan/vulkan.h>

class VulkanDevice;

class VulkanBuffer {
public:
    VulkanBuffer(VulkanDevice* Device, uint32_t Size, VkBufferUsageFlags UsageFlags);

private:
    // Creates a buffer and allocates memory for it
    void CreateBuffer();

private:
    VulkanDevice* Device;

    VkBuffer BufferHandle;

    // Device memory allocation for this buffer
    VkDeviceMemory DeviceMemory;

    uint32_t Size;  // Buffer allocation size
    VkBufferUsageFlags UsageFlags;  // Usage flags for device memory allocation
};

/*
 * https://arm-software.github.io/vulkan_best_practice_for_mobile_developers/samples/performance/layout_transitions/layout_transitions_tutorial.html
 */

class VulkanImage {
public:
    VulkanImage(VulkanDevice* Device, uint32_t Width, uint32_t Height);

private:
    void CreateImage();

private:
    VulkanDevice* Device;

    uint32_t Width, Height;

    VkImage     ImageHandle;
    VkImageView ImageView;

    // Device memory allocation
    VkDeviceMemory DeviceMemory;

    VkImageLayout ImageLayout;
};