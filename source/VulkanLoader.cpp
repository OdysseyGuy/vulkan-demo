#include "VulkanLoader.h"
#include <dlfcn.h>

int LoadVulkanLibrary() {
    void *LibHandle = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
    if (!LibHandle) {
        return 0;
    }

    vkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(dlsym(LibHandle, "vkCreateInstance"));
    vkDestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(dlsym(LibHandle, "vkDestroyInstance"));
    
    vkEnumeratePhysicalDevices =
        reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(dlsym(LibHandle, "vkEnumeratePhysicalDevices"));
    vkGetPhysicalDeviceProperties =
        reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(dlsym(LibHandle, "vkGetPhysicalDeviceProperties"));
    vkGetPhysicalDeviceQueueFamilyProperties =
        reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(dlsym(LibHandle, "vkGetPhysicalDeviceQueueFamilyProperties"));

    vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(dlsym(LibHandle, "vkCreateGraphicsPipelines"));
    vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(dlsym(LibHandle, "vkCreateComputePipelines"));
    vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(dlsym(LibHandle, "vkDestroyPipeline"));

    vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(dlsym(LibHandle, "vkAllocateMemory"));
    vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(dlsym(LibHandle, "vkFreeMemory"));

    return 1;
}

// Instance
PFN_vkCreateInstance vkCreateInstance;
PFN_vkDestroyInstance vkDestroyInstance;

// Physical Device
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;

// Pipelines
PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
PFN_vkCreateComputePipelines vkCreateComputePipelines;
PFN_vkDestroyPipeline vkDestroyPipeline;

// Memory Allocations
PFN_vkAllocateMemory vkAllocateMemory;
PFN_vkFreeMemory vkFreeMemory;