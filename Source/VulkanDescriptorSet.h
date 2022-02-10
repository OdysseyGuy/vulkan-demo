#pragma once

#include "VulkanLoader.h"

/*
 * https://community.arm.com/arm-community-blogs/b/graphics-gaming-and-vr-blog/posts/vulkan-descriptor-and-buffer-management
 * https://github.com/ARM-software/vulkan_best_practice_for_mobile_developers/
 */

class VulkanDevice;


struct VulkanDescriptorSetInfo {

};

class VulkanDescriptorSetLayoutDesc {
public:
    
};

class VulkanDescriptorPool {
public:
    VulkanDescriptorPool(VulkanDevice* Device, VkDescriptorType Type, uint32_t Count);
    ~VulkanDescriptorPool();

    VkDescriptorPool GetHandle() {
        return DescriptorPool;
    }

    void CreateDescriptorPool();
    void Destroy();

private:
    VulkanDevice* Device;

    VkDescriptorPool DescriptorPool;
    VkDescriptorType DescriptorType;
    uint32_t DescriptorCount;
};

class VulkanDescriptorSet {
public:
    VulkanDescriptorSet(
        VulkanDevice* Device,
        VulkanDescriptorPool* DescriptorPool,
        VkDescriptorSetLayout Layout);

    void Allocate();
    void Free();

private:
    VulkanDevice*           Device;
    VulkanDescriptorPool*   DescriptorPool;

    VkDescriptorSet                 DescriptorSet;
    VkDescriptorSetLayoutBinding    Binding;
    VkDescriptorSetLayout           Layout;
};