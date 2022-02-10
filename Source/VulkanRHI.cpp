#include "VulkanCore.h"
#include "VulkanRHI.h"
#include "VulkanDevice.h"

#include <stdio.h>

VulkanRHI::VulkanRHI()
    : Instance(VK_NULL_HANDLE)
{
}

void VulkanRHI::Init() {
    CreateInstance();
    PickAndInitDevice();
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

    VK_CALL(vkCreateInstance(&InstanceCreateInfo, nullptr, &Instance));
}

void VulkanRHI::PickAndInitDevice() {
    uint32_t AvailableGpuCount = 0;
    VK_CALL(vkEnumeratePhysicalDevices(Instance, &AvailableGpuCount, nullptr));

    std::vector<VkPhysicalDevice> AvailableGpus(AvailableGpuCount);
    VK_CALL(vkEnumeratePhysicalDevices(Instance, &AvailableGpuCount, AvailableGpus.data()));

    for (auto CurrGpu: AvailableGpus) {
        VulkanDevice* CurrDevice = new VulkanDevice(CurrGpu);
        VkPhysicalDeviceType Type = CurrDevice->GetGpuProps().deviceType;
        
        // Select the first Discrete GPU
        if (Type == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            Device = CurrDevice;
            break;
        }
    }

    Device->CreateDevice();
}

void VulkanRHI::Shutdown() {
    assert(Device);
    
    Device->WaitUntilIdle(); /* wait for idle state before deletion */
    Device->Destroy();

    delete Device;
    Device = nullptr;

    vkDestroyInstance(Instance, nullptr);
    Instance = VK_NULL_HANDLE;
}