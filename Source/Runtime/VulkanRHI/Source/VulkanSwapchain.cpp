#include "VulkanSwapchain.h"
#include "VulkanPlatform.h"

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

    uint32_t numFormats;
    vkGetPhysicalDeviceSurfaceFormatsKHR(Deve)
}
