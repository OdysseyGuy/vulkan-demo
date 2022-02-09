#include "VulkanCore.h"
#include "VulkanDescriptorSet.h"
#include "VulkanDevice.h"

VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice* InDevice, VkDescriptorType InType, uint32_t InCount)
    : Device(InDevice)
    , DescriptorPool(VK_NULL_HANDLE)
    , DescriptorType(InType)
    , DescriptorCount(InCount)
{
}

void VulkanDescriptorPool::CreateDescriptorPool() {
    VkDescriptorPoolSize DescriptorPoolSize {
        .type = DescriptorType,
        .descriptorCount = DescriptorCount
    };

    VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = DescriptorCount,
        .poolSizeCount = 1,
        .pPoolSizes = &DescriptorPoolSize,
    };

    VK_CALL(vkCreateDescriptorPool(
        Device->GetLogicalDeviceHandle(), &DescriptorPoolCreateInfo, nullptr, &DescriptorPool));
}

void VulkanDescriptorPool::Destroy() {
    vkDestroyDescriptorPool(Device->GetLogicalDeviceHandle(), DescriptorPool, nullptr);
}

VulkanDescriptorSet::VulkanDescriptorSet(VulkanDevice* InDevice, VulkanDescriptorPool* InPool)
    : Device(InDevice)
    , DescriptorPool(InPool)
    , DescriptorSet(VK_NULL_HANDLE)
{   
}

void VulkanDescriptorSet::Allocate() {
    VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = DescriptorPool->GetHandle(),
    };

    VK_CALL(vkAllocateDescriptorSets(
        Device->GetLogicalDeviceHandle(), &DescriptorSetAllocateInfo, &DescriptorSet));
}

void VulkanDescriptorSet::Free() {
}