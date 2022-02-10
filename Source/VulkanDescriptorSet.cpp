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

VulkanDescriptorPool::~VulkanDescriptorPool() {
    vkDestroyDescriptorPool(
        Device->GetLogicalDeviceHandle(), DescriptorPool, nullptr);
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
    DescriptorPool = VK_NULL_HANDLE;
}

VulkanDescriptorSet::VulkanDescriptorSet(
    VulkanDevice* InDevice, VulkanDescriptorPool* InPool, VkDescriptorSetLayout InLayout)
    : Device(InDevice)
    , DescriptorPool(InPool)
    , DescriptorSet(VK_NULL_HANDLE)
    , Layout(InLayout)
{   
}

void VulkanDescriptorSet::Allocate() {
    // Just for reference
    VkDescriptorSetLayoutBinding DescriptorSetLayoutBinding {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        .pImmutableSamplers = nullptr,
    };

    VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &DescriptorSetLayoutBinding,
    };

    VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = DescriptorPool->GetHandle(),
        .descriptorSetCount = 1,
        .pSetLayouts = &Layout,
    };

    // VK_CALL(vkAllocateDescriptorSets(
    //     Device->GetLogicalDeviceHandle(), &DescriptorSetAllocateInfo, &DescriptorSet));
}

void VulkanDescriptorSet::Free() {
    VK_CALL(vkFreeDescriptorSets(
        Device->GetLogicalDeviceHandle(), DescriptorPool->GetHandle(), 1, &DescriptorSet));
}