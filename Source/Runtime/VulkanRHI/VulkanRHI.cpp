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

        .enabledExtensionCount =
            static_cast<uint32_t>(instanceExtensions.size()),
        .ppEnabledExtensionNames = instanceExtensions.data(),
    };

    VK_CALL(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
}

void VulkanRHI::PickAndInitDevice()
{
    uint32_t AvailableGpuCount = 0;
    VK_CALL(vkEnumeratePhysicalDevices(instance, &AvailableGpuCount, nullptr));

    std::vector<VkPhysicalDevice> AvailableGpus(AvailableGpuCount);
    VK_CALL(vkEnumeratePhysicalDevices(instance, &AvailableGpuCount,
                                       AvailableGpus.data()));

    for (auto CurrGpu : AvailableGpus) {
        VulkanDevice        *CurrDevice = new VulkanDevice(CurrGpu);
        VkPhysicalDeviceType Type = CurrDevice->GetGpuProps().deviceType;

        // Select the first Discrete GPU
        if (Type == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            device = CurrDevice;
            break;
        }
    }

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