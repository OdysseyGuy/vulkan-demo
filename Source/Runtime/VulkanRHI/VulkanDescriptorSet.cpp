#include "VulkanDescriptorSet.h"
#include "VulkanCore.h"
#include "VulkanDevice.h"

VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice *inDevice, VkDescriptorType inType,
                                           uint32_t inCount)
    : device(inDevice), descriptorPool(VK_NULL_HANDLE), descriptorType(inType),
      descriptorCount(inCount)
{
}

VulkanDescriptorPool::~VulkanDescriptorPool()
{
    vkDestroyDescriptorPool(device->GetLogicalDeviceHandle(), descriptorPool, nullptr);
}

void VulkanDescriptorPool::CreateDescriptorPool()
{
    VkDescriptorPoolSize descriptorPoolSize{.type = descriptorType,
                                            .descriptorCount = descriptorCount};

    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = descriptorCount,
        .poolSizeCount = 1,
        .pPoolSizes = &descriptorPoolSize,
    };

    VK_CALL(vkCreateDescriptorPool(device->GetLogicalDeviceHandle(), &descriptorPoolCreateInfo,
                                   nullptr, &descriptorPool));
}

void VulkanDescriptorPool::Destroy()
{
    vkDestroyDescriptorPool(device->GetLogicalDeviceHandle(), descriptorPool, nullptr);
    descriptorPool = VK_NULL_HANDLE;
}

VulkanDescriptorSet::VulkanDescriptorSet(VulkanDevice *inDevice, VulkanDescriptorPool *inPool,
                                         VkDescriptorSetLayout inLayout)
    : device(inDevice), descriptorPool(inPool), descriptorSet(VK_NULL_HANDLE), layout(inLayout)
{
}

void VulkanDescriptorSet::Allocate()
{
    // Just for reference
    // VkDescriptorSetLayoutBinding descriptorSetLayoutBinding{
    //     .binding = 0,
    //     .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
    //     .descriptorCount = 1,
    //     .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
    //     .pImmutableSamplers = nullptr,
    // };

    // VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{
    //     .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
    //     .bindingCount = 1,
    //     .pBindings = &descriptorSetLayoutBinding,
    // };

    // VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo{
    //     .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
    //     .descriptorPool = descriptorPool->GetHandle(),
    //     .descriptorSetCount = 1,
    //     .pSetLayouts = &layout,
    // };

    // VK_CALL(vkAllocateDescriptorSets(
    //     device->GetLogicalDeviceHandle(), &descriptorSetAllocateInfo,
    //     &descriptorSet));
}

void VulkanDescriptorSet::Free()
{
    VK_CALL(vkFreeDescriptorSets(device->GetLogicalDeviceHandle(), descriptorPool->GetHandle(), 1,
                                 &descriptorSet));
}
