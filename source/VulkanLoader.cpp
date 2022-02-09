#include "VulkanLoader.h"
#include <dlfcn.h>

int LoadVulkanLibrary() {
    void *LibHandle = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
    if (!LibHandle) {
        return 0;
    }

    vkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(dlsym(LibHandle, "vkCreateInstance"));
    vkDestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(dlsym(LibHandle, "vkDestroyInstance"));

    vkCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(dlsym(LibHandle, "vkCreateDevice"));
    vkDestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(dlsym(LibHandle, "vkDestroyDevice"));

    vkGetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(dlsym(LibHandle, "vkGetDeviceQueue"));
    
    vkEnumeratePhysicalDevices =
        reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(dlsym(LibHandle, "vkEnumeratePhysicalDevices"));
    vkGetPhysicalDeviceProperties =
        reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(dlsym(LibHandle, "vkGetPhysicalDeviceProperties"));
    vkGetPhysicalDeviceQueueFamilyProperties =
        reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(dlsym(LibHandle, "vkGetPhysicalDeviceQueueFamilyProperties"));

    vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(dlsym(LibHandle, "vkCreateGraphicsPipelines"));
    vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(dlsym(LibHandle, "vkCreateComputePipelines"));
    vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(dlsym(LibHandle, "vkDestroyPipeline"));

    vkGetBufferMemoryRequirements = 
        reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(dlsym(LibHandle, "vkGetBufferMemoryRequirements"));
    vkGetImageMemoryRequirements =
        reinterpret_cast<PFN_vkGetImageMemoryRequirements>(dlsym(LibHandle, "vkGetImageMemoryRequirements"));

    vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(dlsym(LibHandle, "vkAllocateMemory"));
    vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(dlsym(LibHandle, "vkFreeMemory"));

    vkCreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(dlsym(LibHandle, "vkCreateCommandPool"));
    vkDestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(dlsym(LibHandle, "vkDestroyCommandPool"));

    vkAllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(dlsym(LibHandle, "vkAllocateCommandBuffers"));
    vkFreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(dlsym(LibHandle, "vkFreeCommandBuffers"));
    vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(dlsym(LibHandle, "vkBeginCommandBuffer"));
    vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(dlsym(LibHandle, "vkEndCommandBuffer"));

    vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(dlsym(LibHandle, "vkCreateBuffer"));
    vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(dlsym(LibHandle, "vkCreateImage"));

    return 1;
}

PFN_vkCreateInstance vkCreateInstance;
PFN_vkDestroyInstance vkDestroyInstance;

PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;

PFN_vkCreateDevice vkCreateDevice;
PFN_vkDestroyDevice vkDestroyDevice;

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

PFN_vkCreateBuffer vkCreateBuffer;

PFN_vkCreateImage vkCreateImage;