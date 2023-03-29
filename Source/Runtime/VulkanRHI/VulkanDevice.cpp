#include "VulkanDevice.h"
#include "VulkanCore.h"
#include "VulkanDescriptorSet.h"

VulkanDevice::VulkanDevice(VkPhysicalDevice InGpu)
    : device(VK_NULL_HANDLE)
    , gpu(InGpu)
{
    vkGetPhysicalDeviceProperties(gpu, &gpuProps);
}

VulkanDevice::~VulkanDevice()
{
    if (device != VK_NULL_HANDLE) {
        Destroy();
        device = VK_NULL_HANDLE;
    }
}

void VulkanDevice::CreateDevice()
{
    // Memory properties
    vkGetPhysicalDeviceMemoryProperties(gpu, &gpuMemoryProps);

    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyProperties(
        queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueFamilyCount,
                                             queueFamilyProperties.data());

    // Create Queue Infos Per Queue Family
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(queueFamilyCount);

    int32_t graphicsQueueFamilyIndex = -1;
    int32_t computeQueueFamilyIndex = -1;

    uint32_t totalQueueCount = 0;

    for (uint32_t familyIndex = 0;
         familyIndex < (uint32_t)queueFamilyProperties.size(); ++familyIndex) {
        const VkQueueFamilyProperties &CurrProps =
            queueFamilyProperties[familyIndex];

        if (queueFamilyProperties[familyIndex].queueFlags &
            VK_QUEUE_GRAPHICS_BIT) {
            graphicsQueueFamilyIndex = familyIndex;
        }
        if (queueFamilyProperties[familyIndex].queueFlags &
            VK_QUEUE_COMPUTE_BIT) {
            computeQueueFamilyIndex = familyIndex;
        }

        VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = familyIndex,
            .queueCount = CurrProps.queueCount,
        };

        queueCreateInfos.emplace_back(deviceQueueCreateInfo);
        totalQueueCount += CurrProps.queueCount;
    }

    // set queue priorities
    std::vector<float> queuePriorities(totalQueueCount);
    float             *currentPriority = queuePriorities.data();

    for (uint32_t Index = 0; Index < (uint32_t)queueCreateInfos.size();
         ++Index) {
        VkDeviceQueueCreateInfo &createInfo = queueCreateInfos[Index];
        createInfo.pQueuePriorities = currentPriority;

        VkQueueFamilyProperties &CurrProps = queueFamilyProperties[Index];

        /* set all of them to 1.0f */
        for (uint32_t CurrentQueueIndex = 0;
             CurrentQueueIndex < (uint32_t)CurrProps.queueCount;
             ++CurrentQueueIndex) {
            *(currentPriority++) = 1.0f;
        }
    }

    // Create Logical device
    VkDeviceCreateInfo deviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
        .pQueueCreateInfos = queueCreateInfos.data(),
        .enabledLayerCount = static_cast<uint32_t>(deviceLayers.size()),
        .ppEnabledLayerNames = deviceLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
        .ppEnabledExtensionNames = deviceExtensions.data()};

    VK_CALL(vkCreateDevice(gpu, &deviceCreateInfo, nullptr, &device));

    // Get Queue Handles
    vkGetDeviceQueue(device, graphicsQueueFamilyIndex, 0, &graphicsQueue);
    vkGetDeviceQueue(device, computeQueueFamilyIndex, 0, &computeQueue);

    descriptorPool =
        new VulkanDescriptorPool(this, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
}

void VulkanDevice::WaitUntilIdle() { VK_CALL(vkDeviceWaitIdle(device)); }

void VulkanDevice::Destroy()
{
    vkDestroyDevice(device, nullptr);
    device = VK_NULL_HANDLE;
}

int32_t
FindMemoryTypeIndex(VkPhysicalDeviceMemoryProperties gpuMemoryProperties,
                    uint32_t                         memoryTypeBitsRequirement,
                    VkMemoryPropertyFlags            propertiesRequirement)
{
    const uint32_t memoryTypeCount = gpuMemoryProperties.memoryTypeCount;
    for (uint32_t memoryIndex = 0; memoryIndex < memoryTypeCount;
         ++memoryIndex) {
        uint32_t MemoryTypeBits = (1 << memoryIndex);

        /* look for required property flags */
        const VkMemoryPropertyFlags propertiesFlags =
            gpuMemoryProperties.memoryTypes[memoryIndex].propertyFlags;

        /* is required memory type and has required properties */
        if ((MemoryTypeBits & memoryTypeBitsRequirement) &&
            (propertiesFlags & propertiesRequirement) ==
                propertiesRequirement) {
            return static_cast<int32_t>(memoryIndex);
        }
    }

    return -1;
}

void VulkanDevice::AllocateDeviceMemory(VkDeviceMemory deviceMemory,
                                        VkFlags        flags)
{

    VkMemoryAllocateInfo memoryAllocateInfo{
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    };

    VK_CALL(
        vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &deviceMemory));
}