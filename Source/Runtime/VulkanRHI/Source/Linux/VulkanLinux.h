#pragma once

#include <vector>
#include "../VulkanLoader.h"

class LinuxVulkan
{
public:
    static bool LoadVulkanLibrary();
    static void FreeVulkanLibrary();

    static void GetIntanceExtenstions(std::vector<const char *> &outExt);
    // static void GetIntanceLayers(std::vector<uint32_t> &outLayers);
    // void GetDeviceExtenstions(std::vector<const char *> &outExt);
    // void GetDeviceLayers(std::vector<uint32_t> &outLayers);

    static void CreateSurface(void *windowHandle, VkInstance instance, VkSurfaceKHR *outSurface);

private:
    static void *vulkanHandle;
};

typedef LinuxVulkan PlatformVulkan;
