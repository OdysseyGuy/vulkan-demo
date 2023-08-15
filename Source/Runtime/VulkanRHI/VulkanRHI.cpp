#include "VulkanRHI.h"
#include "VulkanCore.h"
#include "VulkanDevice.h"

#include <stdio.h>

VulkanRHI::VulkanRHI()
    : instance(VK_NULL_HANDLE)
{
}

void VulkanRHI::Init()
{
    CreateInstance();
    PickAndInitDevice();
}

void VulkanRHI::CreateInstance()
{
    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "VulkanDemoRenderer",
        .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
        .pEngineName = "VulkanDemoRenderer",
        .engineVersion = VK_MAKE_VERSION(0, 0, 1),
        .apiVersion = static_cast<uint32_t>(VK_API_VERSION_1_0),
    };

    VkInstanceCreateInfo instanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32_t>(instanceLayers.size()),
        .ppEnabledLayerNames = instanceLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size()),
        .ppEnabledExtensionNames = instanceExtensions.data(),
    };

    VK_CALL(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
}

void VulkanRHI::PickAndInitDevice()
{
    // UE does this in the constructor
    uint32_t availableGpuCount = 0;
    VkResult result = vkEnumeratePhysicalDevices(instance, &availableGpuCount, nullptr);
    if (result == VK_ERROR_INITIALIZATION_FAILED) {
        // Error failed to find any vulkan drivers
    }

    std::vector<VkPhysicalDevice> availableGpus(availableGpuCount);
    VK_CALL(vkEnumeratePhysicalDevices(instance, &availableGpuCount, availableGpus.data()));

    std::vector<VulkanDevice *> devices;

    for (auto currGpu : availableGpus) {
        VulkanDevice *currDevice = new VulkanDevice(currGpu);
        devices.emplace_back(currDevice);

        // VkPhysicalDeviceType type = currDevice->GetGpuProps().deviceType;

        // bool isDiscrete = (type == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
        // bool isCpuDevice = (type == VK_PHYSICAL_DEVICE_TYPE_CPU);

        // Select the first Discrete GPU
        // if (isDiscrete) {
        //     device = currDevice;
        //     break;
        // }
    }

    // For now just choose the first one
    device = devices[0];

    // UE does this in the Init() function
    device->CreateDevice();
}

void VulkanRHI::Shutdown()
{
    assert(device);

    device->WaitUntilIdle(); /* wait for idle state before deletion */
    device->Destroy();

    delete device;
    device = nullptr;

    vkDestroyInstance(instance, nullptr);
    instance = VK_NULL_HANDLE;
}
