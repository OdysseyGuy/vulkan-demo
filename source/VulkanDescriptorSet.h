#pragma once

#include <vulkan/vulkan.h>

class VulkanDevice;

class VulkanDescriptorSetLayoutDesc {
public:

};

class VulkanDescriptorPool {
public:
    VulkanDescriptorPool(VulkanDevice* Device, VkDescriptorType Type, uint32_t Count);

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
    VulkanDescriptorSet(VulkanDevice* Device, VulkanDescriptorPool* DescriptorPool);

    void Allocate();
    void Free();

private:
    VulkanDevice*           Device;
    VulkanDescriptorPool*   DescriptorPool;

    VkDescriptorSet                 DescriptorSet;
    VkDescriptorSetLayoutBinding    Binding;
    VkDescriptorSetLayout           Layout;
};