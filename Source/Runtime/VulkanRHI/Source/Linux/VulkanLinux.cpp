#include "VulkanLinux.h"
#include <dlfcn.h>
#include <cassert>
#include "SDL3/SDL_vulkan.h"
#include "Linux/LinuxPlatform.h"

void *LinuxVulkan::vulkanHandle = nullptr;

bool LinuxVulkan::LoadVulkanLibrary()
{
    vulkanHandle = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
    if (vulkanHandle == nullptr) {
        return false;
    }
}

void LinuxVulkan::FreeVulkanLibrary()
{
    if (vulkanHandle != nullptr) {
        dlclose(vulkanHandle);
        vulkanHandle = nullptr;
    }
}

void LinuxVulkan::GetIntanceExtenstions(std::vector<const char *> &outExt)
{
    if (!LinuxPlatform::InitSDL()) {
        assert(0);
    }

    const char *sdlDriver = SDL_GetCurrentVideoDriver();
    if (sdlDriver == nullptr) {
        return;
    }

    if (SDL_strcmp(sdlDriver, "x11") == 0) {
        outExt.emplace_back("VK_KHR_xlib_surface");
    } else if (SDL_strcmp(sdlDriver, "wayland") == 0) {
        outExt.emplace_back("VK_KHR_wayland_surface");
    } else {
        assert(0);
    }
}

void LinuxVulkan::CreateSurface(void *windowHandle, VkInstance instance, VkSurfaceKHR *outSurface)
{
    if (!LinuxPlatform::InitSDL()) {
        assert(0);
    }

    if (SDL_Vulkan_CreateSurface((SDL_Window *)windowHandle, instance, outSurface) == SDL_FALSE) {
        assert(0);
    }
}
