#pragma once

#include "VulkanLoader.h"
#include <vector>

class VulkanDevice;

class VulkanSwapchain
{
public:
    VulkanSwapchain(VkInstance instance, VulkanDevice &device, uint32_t &inOutPixelFormat,
                    void *windowHandle, uint32_t width, uint32_t height,
                    std::vector<VkImage> &outImages);

private:
    VkSwapchainKHR swapchain;
    VulkanDevice &device;

    VkSurfaceKHR surface;
    void *windowHandle;

    VkInstance instance;
};
