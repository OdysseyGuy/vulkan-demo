#include "VulkanDevice.h"
#include "VulkanCore.h"
#include "VulkanDescriptorSet.h"

VulkanDevice::VulkanDevice(VkPhysicalDevice InGpu)
    : Device(VK_NULL_HANDLE)
    , Gpu(InGpu)
{
    vkGetPhysicalDeviceProperties(Gpu, &GpuProps);
}

VulkanDevice::~VulkanDevice() {
    if (Device != VK_NULL_HANDLE) {
        Destroy();
        Device = VK_NULL_HANDLE;
    }
}

void VulkanDevice::CreateDevice() {
    // Memory properties
    vkGetPhysicalDeviceMemoryProperties(Gpu, &GpuMemoryProps);

    uint32_t QueueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(Gpu, &QueueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> QueueFamilyProperties(QueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(Gpu, &QueueFamilyCount, QueueFamilyProperties.data());

    // Create Queue Infos Per Queue Family
    std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;

    int32_t GraphicsQueueFamilyIndex = -1;
    int32_t ComputeQueueFamilyIndex = -1;

    uint32_t TotalQueueCount = 0;

    for (uint32_t FamilyIndex = 0; FamilyIndex < (uint32_t)QueueFamilyProperties.size(); ++FamilyIndex) {
        const VkQueueFamilyProperties& CurrProps = QueueFamilyProperties[FamilyIndex];

        if (QueueFamilyProperties[FamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            GraphicsQueueFamilyIndex = FamilyIndex;
        }
        if (QueueFamilyProperties[FamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT) {
            ComputeQueueFamilyIndex = FamilyIndex;
        }

        VkDeviceQueueCreateInfo DeviceQueueCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = FamilyIndex,
            .queueCount = CurrProps.queueCount,
        };

        QueueCreateInfos.emplace_back(DeviceQueueCreateInfo);
        TotalQueueCount += CurrProps.queueCount;
    }

    // set queue priorities
    std::vector<float> QueuePriorities(TotalQueueCount);
    float *CurrentPriority = QueuePriorities.data();

    for (uint32_t Index = 0; Index < (uint32_t)QueueCreateInfos.size(); ++Index) {
        VkDeviceQueueCreateInfo& CreateInfo = QueueCreateInfos[Index];
        CreateInfo.pQueuePriorities = CurrentPriority;
        
        VkQueueFamilyProperties &CurrProps = QueueFamilyProperties[Index];
        
        /* set all of them to 1.0f */
        for (
            uint32_t CurrentQueueIndex = 0;
            CurrentQueueIndex < (uint32_t)CurrProps.queueCount;
            ++CurrentQueueIndex
        ) {
            *(CurrentPriority++) = 1.0f;
        }
    }

    // Create Logical device
    VkDeviceCreateInfo DeviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfos.size()),
        .pQueueCreateInfos = QueueCreateInfos.data(),
        .enabledLayerCount = static_cast<uint32_t>(DeviceLayers.size()),
        .ppEnabledLayerNames = DeviceLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size()),
        .ppEnabledExtensionNames = DeviceExtensions.data()
    };

    VK_CALL(vkCreateDevice(Gpu, &DeviceCreateInfo, nullptr, &Device));
    
    // Get Queue Handles
    vkGetDeviceQueue(Device, GraphicsQueueFamilyIndex, 0, &GraphicsQueue);
    vkGetDeviceQueue(Device, ComputeQueueFamilyIndex, 0, &ComputeQueue);

    DescriptorPool = new VulkanDescriptorPool(this, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
}

void VulkanDevice::WaitUntilIdle() {
    VK_CALL(vkDeviceWaitIdle(Device));
}

void VulkanDevice::Destroy() {
    vkDestroyDevice(Device, nullptr);
    Device = VK_NULL_HANDLE;
}

int32_t FindMemoryTypeIndex(VkPhysicalDeviceMemoryProperties GpuMemoryProperties,
                            uint32_t MemoryTypeBitsRequirement,
                            VkMemoryPropertyFlags PropertiesRequirement) {
    const uint32_t MemoryTypeCount = GpuMemoryProperties.memoryTypeCount;
    for (uint32_t MemoryIndex = 0; MemoryIndex < MemoryTypeCount; ++MemoryIndex) {
        uint32_t MemoryTypeBits = (1 << MemoryIndex);

        /* look for required property flags */
        const VkMemoryPropertyFlags PropertiesFlags =
                GpuMemoryProperties.memoryTypes[MemoryIndex].propertyFlags;

        /* is required memory type and has required properties */
        if ((MemoryTypeBits & MemoryTypeBitsRequirement) &&
                (PropertiesFlags & PropertiesRequirement) == PropertiesRequirement) {
            return static_cast<int32_t>(MemoryIndex);
        }
    }

    return -1;
}

void VulkanDevice::AllocateDeviceMemory(VkDeviceMemory DeviceMemory, VkFlags Flags) {

    VkMemoryAllocateInfo MemoryAllocateInfo {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    };

    VK_CALL(vkAllocateMemory(Device, &MemoryAllocateInfo, nullptr, &DeviceMemory));
}