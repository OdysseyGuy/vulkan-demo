#include "VulkanCore.h"
#include "VulkanRHI.h"
#include "VulkanDevice.h"

#include <vector>
#include <vulkan/vulkan.h>

VulkanRHI::VulkanRHI()
    : Instance(VK_NULL_HANDLE)
{
}

void VulkanRHI::CreateInstance() {
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
}

void VulkanRHI::PickAndInitGpu() {
    uint32_t AvailableGpuCount = 0;
    VK_CALL(vkEnumeratePhysicalDevices(Instance, &AvailableGpuCount, nullptr));

    std::vector<VkPhysicalDevice> AvailableGpus(AvailableGpuCount);
    VK_CALL(vkEnumeratePhysicalDevices(Instance, &AvailableGpuCount, AvailableGpus.data()));

    // for now just pick the first available device
    Device = new VulkanDevice(AvailableGpus[0]);

    Device->CreateDevice();
}

void VulkanRHI::Shutdown() {
    Device->Destroy();
    vkDestroyInstance(Instance, nullptr);
}