#pragma once

#define VK_NO_PROTOTYPES 1
#include "vulkan/vulkan.h"

// Instance
extern PFN_vkCreateInstance vkCreateInstance;
extern PFN_vkDestroyInstance vkDestroyInstance;

// Physical Device
extern PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
extern PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;

// Logical Device
extern PFN_vkCreateDevice vkCreateDevice;
extern PFN_vkDestroyDevice vkDestroyDevice;
extern PFN_vkDeviceWaitIdle vkDeviceWaitIdle;

// Device Queue
extern PFN_vkGetDeviceQueue vkGetDeviceQueue;

// Pipelines
extern PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
extern PFN_vkCreateComputePipelines vkCreateComputePipelines;
extern PFN_vkDestroyPipeline vkDestroyPipeline;

// Memory Properties
extern PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;

// Memory Requirements
extern PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
extern PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;

// Device Memory Allocations
extern PFN_vkAllocateMemory vkAllocateMemory;
extern PFN_vkFreeMemory vkFreeMemory;

// Command Pool
extern PFN_vkCreateCommandPool vkCreateCommandPool;
extern PFN_vkDestroyCommandPool vkDestroyCommandPool;

// Command Buffer
extern PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
extern PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
extern PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
extern PFN_vkEndCommandBuffer vkEndCommandBuffer;

// Commands
extern PFN_vkCmdDraw vkCmdDraw;
extern PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
extern PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
extern PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
extern PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
extern PFN_vkCmdClearAttachments vkCmdClearAttachments;
extern PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
extern PFN_vkCmdDispatch vkCmdDispatch;
extern PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;

// Render Pass
extern PFN_vkCreateRenderPass2 vkCreateRenderPass2;

// Descriptor Pool
extern PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
extern PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;

// Descriptor Sets
extern PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
extern PFN_vkFreeDescriptorSets vkFreeDescriptorSets;

// Buffers
extern PFN_vkCreateBuffer vkCreateBuffer;

// Images
extern PFN_vkCreateImage vkCreateImage;

// Swapchain
extern PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
extern PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
extern PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
