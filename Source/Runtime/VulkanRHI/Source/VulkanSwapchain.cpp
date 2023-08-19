#include "VulkanSwapchain.h"
#include "VulkanPlatform.h"
#include "VulkanDevice.h"

VulkanSwapchain::VulkanSwapchain(VkInstance inInstance, VulkanDevice &inDevice,
                                 uint32_t &inOutPixelFormat, void *inWindowHandle, uint32_t width,
                                 uint32_t height, std::vector<VkImage> &outImages)
    : swapchain(VK_NULL_HANDLE)
    , device(inDevice)
    , surface(VK_NULL_HANDLE)
    , windowHandle(inWindowHandle)
    , instance(inInstance)
{
    PlatformVulkan::CreateSurface(windowHandle, instance, &surface);

    VkPhysicalDeviceSurfaceInfo2KHR surfaceInfo2 = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR,
        .pNext = nullptr,
        .surface = surface,
    };

    uint32_t numFormats;
    vkGetPhysicalDeviceSurfaceFormats2KHR(device.GetPhysicalDeviceHandle(), &surfaceInfo2,
                                          &numFormats, nullptr);

    std::vector<VkSurfaceFormat2KHR> surfaceFormats;
    vkGetPhysicalDeviceSurfaceFormats2KHR(device.GetPhysicalDeviceHandle(), &surfaceInfo2,
                                          &numFormats, surfaceFormats.data());

    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

    uint32_t numPresetModes = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device.GetPhysicalDeviceHandle(), surface,
                                              &numPresetModes, nullptr);

    std::vector<VkPresentModeKHR> presentModes;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device.GetPhysicalDeviceHandle(), surface,
                                              &numPresetModes, presentModes.data());

    VkSurfaceCapabilities2KHR surfaceCaps;
    vkGetPhysicalDeviceSurfaceCapabilities2KHR(device.GetPhysicalDeviceHandle(), &surfaceInfo2,
                                               &surfaceCaps);
}
