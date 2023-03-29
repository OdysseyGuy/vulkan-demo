/*****************************************************
    Code for Vulkan Graphics and Compute Pipelines
******************************************************/

#pragma once

#include "VulkanCore.h"
#include "VulkanLoader.h"

class VulkanDevice;

struct VulkanGraphicsPipelineStateDesc {
    /* Input Assembly state */
    VkPrimitiveTopology topology;

    /* Rasterizer */
    VkPolygonMode   polygonMode;
    VkCullModeFlags cullMode;
    float           depthBiasSlopeFactor;
    float           depthBiasConstantFactor;

    /* Depth Stencil */
    VkCompareOp      depthCompareOp;
    VkStencilOpState front;
    VkStencilOpState back;
    bool             depthTestEnable;
    bool             depthWriteEnable;
    bool             stencilTestEnable;
    bool             depthBoundsTestEnable;
};

// TODO: Implement PSO cache
class VulkanPipelineStateCache
{
public:
    void Load(); /* Load from disk */
    void Save(); /* Saves to disk */
private:
    VkPipelineCache pipelineCache;
};

// TODO: Need to provide Descriptor Set and Descriptor Layout
class VulkanGraphicsPipeline
{
public:
    VulkanGraphicsPipeline(VulkanDevice *inDevice);

private:
    void CreateGraphicsPipeline();

private:
    VulkanDevice *device;

    VkPipeline pipeline;
    /* descriptor set layouts + push constant ranges */
    VkPipelineLayout pipelineLayout;

    // Shader modules per Pipeline shader stage
    VkShaderModule shaderStageModules[ShaderStage::Num];

    VulkanGraphicsPipelineStateDesc desc;
};

class VulkanComputePipeline
{
public:
    VulkanComputePipeline(VulkanDevice *inDevice);

private:
    void CreateComputePipeline();

private:
    VulkanDevice *device;

    VkPipeline       pipeline;
    VkPipelineLayout pipelineLayout;

    // Compute shader bindings
    VkDescriptorSet       descriptorSet;
    VkDescriptorSetLayout descriptorSetLayout; /* binding layout */

    VkShaderModule computeShaderModule;
};