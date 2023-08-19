#pragma once

#include "VulkanLoader.h"

/*
 * https://community.arm.com/arm-community-blogs/b/graphics-gaming-and-vr-blog/posts/vulkan-descriptor-and-buffer-management
 * https://github.com/ARM-software/vulkan_best_practice_for_mobile_developers/
 */

class VulkanDevice;

struct VulkanDescriptorSetInfo
{
};

class VulkanDescriptorSetLayoutDesc
{
public:
};

class VulkanDescriptorPool
{
public:
    VulkanDescriptorPool(VulkanDevice *device, VkDescriptorType type, uint32_t count);
    ~VulkanDescriptorPool();

    VkDescriptorPool GetHandle()
    {
        return descriptorPool;
    }

    void CreateDescriptorPool();
    void Destroy();

private:
    VulkanDevice *device;

    VkDescriptorPool descriptorPool;
    VkDescriptorType descriptorType;
    uint32_t descriptorCount;
};

class VulkanDescriptorSet
{
public:
    VulkanDescriptorSet(VulkanDevice *device, VulkanDescriptorPool *descriptorPool,
                        VkDescriptorSetLayout layout);

    void Allocate();
    void Free();

private:
    VulkanDevice *device;
    VulkanDescriptorPool *descriptorPool;

    VkDescriptorSet descriptorSet;
    VkDescriptorSetLayoutBinding binding;
    VkDescriptorSetLayout layout;
};
