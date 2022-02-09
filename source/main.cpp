#include "VulkanLoader.h"

#include <vector>
#include <iostream>

#include <vulkan/vulkan_core.h>

int main(int argc, char const *argv[]) {
    if (!LoadVulkanLibrary()) {
        std::cout << "Failed to initialize Vulkan Library!" << std::endl;
    }

    VkInstance Instance = VK_NULL_HANDLE;

    std::vector<const char*> InstanceLayers;
    std::vector<const char*> InstanceExtensions;

    VkApplicationInfo AppInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        
        .pApplicationName = "VulkanDemoRenderer",
        .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
        
        .pEngineName = "VulkanDemoRenderer",
        .engineVersion = VK_MAKE_VERSION(0, 0, 1),
        
        .apiVersion = static_cast<uint32_t>(VK_API_VERSION_1_0),
    };

    VkInstanceCreateInfo InstanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &AppInfo,
        .enabledLayerCount = static_cast<uint32_t>(InstanceLayers.size()),
        .ppEnabledLayerNames = InstanceLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(InstanceExtensions.size()),
        .ppEnabledExtensionNames = InstanceExtensions.data(),
    };

    vkCreateInstance(&InstanceCreateInfo, nullptr, &Instance);

    // Find available GPUs
    uint32_t AvailableGpuCount = 0;
    vkEnumeratePhysicalDevices(Instance, &AvailableGpuCount, nullptr);

    std::vector<VkPhysicalDevice> AvailableGpus(AvailableGpuCount);
    vkEnumeratePhysicalDevices(Instance, &AvailableGpuCount, AvailableGpus.data());

    VkPhysicalDevice Gpu = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties GpuProperties;

    VkQueue GraphicsQueue;
    VkQueue ComputeQueue;

    int32_t GraphicsQueueFamilyIndex = -1;
    int32_t ComputeQueueFamilyIndex = -1;

    // For async compute we need a seperate compute queue
    bool bHasAsyncCompute = false;

    for (auto GpuDevice: AvailableGpus) {
        uint32_t QueueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(GpuDevice, &QueueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> QueueFamilyProperties(QueueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(GpuDevice, &QueueFamilyCount, QueueFamilyProperties.data());

        int32_t FamilyIndex = -1;

        for (int32_t i = 0; i < QueueFamilyProperties.size(); ++i) {
            if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                GraphicsQueueFamilyIndex = i;
                FamilyIndex = i;
            }
            else {
                if (QueueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
                    ComputeQueueFamilyIndex = i;
                }
            }
        }

        if (FamilyIndex < 0) continue;

        Gpu = GpuDevice;

        if (ComputeQueueFamilyIndex < 0) {
            // Set Graphics queue as compute queue
            ComputeQueueFamilyIndex = GraphicsQueueFamilyIndex;
        }
        if (GraphicsQueueFamilyIndex != ComputeQueueFamilyIndex) {
            // Has seperate compute queue
            bHasAsyncCompute = true;
        }
    }

    VkPhysicalDeviceProperties GpuProps;
    vkGetPhysicalDeviceProperties(Gpu, &GpuProps);

    // Logical device
    VkDevice Device;
    


    vkDestroyInstance(Instance, nullptr);

    return 0;
}