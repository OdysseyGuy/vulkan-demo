#include "VulkanLoader.h"
#include <dlfcn.h>

#define LOAD_VK_SYMBOL(sym, lib) sym = reinterpret_cast<PFN_##sym>(dlsym(lib, #sym))

int LoadVulkanLibrary()
{
    void *libHandle = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
    if (!libHandle) {
        return 0;
    }

    LOAD_VK_SYMBOL(vkCreateInstance, libHandle);
    LOAD_VK_SYMBOL(vkDestroyInstance, libHandle);

    LOAD_VK_SYMBOL(vkCreateDevice, libHandle);
    LOAD_VK_SYMBOL(vkDestroyDevice, libHandle);
    LOAD_VK_SYMBOL(vkDeviceWaitIdle, libHandle);

    LOAD_VK_SYMBOL(vkGetDeviceQueue, libHandle);

    LOAD_VK_SYMBOL(vkEnumeratePhysicalDevices, libHandle);
    LOAD_VK_SYMBOL(vkGetPhysicalDeviceProperties, libHandle);
    LOAD_VK_SYMBOL(vkGetPhysicalDeviceQueueFamilyProperties, libHandle);

    LOAD_VK_SYMBOL(vkCreateGraphicsPipelines, libHandle);
    LOAD_VK_SYMBOL(vkCreateComputePipelines, libHandle);
    LOAD_VK_SYMBOL(vkDestroyPipeline, libHandle);

    LOAD_VK_SYMBOL(vkGetPhysicalDeviceMemoryProperties, libHandle);

    LOAD_VK_SYMBOL(vkGetBufferMemoryRequirements, libHandle);
    LOAD_VK_SYMBOL(vkGetImageMemoryRequirements, libHandle);

    LOAD_VK_SYMBOL(vkAllocateMemory, libHandle);
    LOAD_VK_SYMBOL(vkFreeMemory, libHandle);

    LOAD_VK_SYMBOL(vkCreateCommandPool, libHandle);
    LOAD_VK_SYMBOL(vkDestroyCommandPool, libHandle);

    LOAD_VK_SYMBOL(vkAllocateCommandBuffers, libHandle);
    LOAD_VK_SYMBOL(vkFreeCommandBuffers, libHandle);
    LOAD_VK_SYMBOL(vkBeginCommandBuffer, libHandle);
    LOAD_VK_SYMBOL(vkEndCommandBuffer, libHandle);

    LOAD_VK_SYMBOL(vkCmdDraw, libHandle);
    LOAD_VK_SYMBOL(vkCmdDrawIndirect, libHandle);
    LOAD_VK_SYMBOL(vkCmdBindIndexBuffer, libHandle);
    LOAD_VK_SYMBOL(vkCmdDrawIndexed, libHandle);
    LOAD_VK_SYMBOL(vkCmdDrawIndexedIndirect, libHandle);
    LOAD_VK_SYMBOL(vkCmdClearAttachments, libHandle);
    LOAD_VK_SYMBOL(vkCmdCopyBuffer, libHandle);
    LOAD_VK_SYMBOL(vkCmdDispatch, libHandle);
    LOAD_VK_SYMBOL(vkCmdDispatchIndirect, libHandle);

    LOAD_VK_SYMBOL(vkCreateRenderPass2, libHandle);

    LOAD_VK_SYMBOL(vkCreateDescriptorPool, libHandle);
    LOAD_VK_SYMBOL(vkDestroyDescriptorPool, libHandle);

    LOAD_VK_SYMBOL(vkAllocateDescriptorSets, libHandle);
    LOAD_VK_SYMBOL(vkFreeDescriptorSets, libHandle);

    LOAD_VK_SYMBOL(vkCreateBuffer, libHandle);
    LOAD_VK_SYMBOL(vkCreateImage, libHandle);

    LOAD_VK_SYMBOL(vkGetPhysicalDeviceSurfaceCapabilities2KHR, libHandle);
    LOAD_VK_SYMBOL(vkGetPhysicalDeviceSurfaceSupportKHR, libHandle);
    LOAD_VK_SYMBOL(vkCreateSwapchainKHR, libHandle);
    LOAD_VK_SYMBOL(vkGetSwapchainImagesKHR, libHandle);

    return 1;
}

PFN_vkCreateInstance vkCreateInstance;
PFN_vkDestroyInstance vkDestroyInstance;

PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;

PFN_vkCreateDevice vkCreateDevice;
PFN_vkDestroyDevice vkDestroyDevice;
PFN_vkDeviceWaitIdle vkDeviceWaitIdle;

PFN_vkGetDeviceQueue vkGetDeviceQueue;

PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
PFN_vkCreateComputePipelines vkCreateComputePipelines;
PFN_vkDestroyPipeline vkDestroyPipeline;

PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;

PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;

PFN_vkAllocateMemory vkAllocateMemory;
PFN_vkFreeMemory vkFreeMemory;

PFN_vkCreateCommandPool vkCreateCommandPool;
PFN_vkDestroyCommandPool vkDestroyCommandPool;

PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
PFN_vkEndCommandBuffer vkEndCommandBuffer;

PFN_vkCmdDraw vkCmdDraw;
PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
PFN_vkCmdClearAttachments vkCmdClearAttachments;
PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
PFN_vkCmdDispatch vkCmdDispatch;
PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;

PFN_vkCreateRenderPass2 vkCreateRenderPass2;

PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;

PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
PFN_vkFreeDescriptorSets vkFreeDescriptorSets;

PFN_vkCreateBuffer vkCreateBuffer;

PFN_vkCreateImage vkCreateImage;

PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
