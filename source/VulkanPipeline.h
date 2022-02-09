/*****************************************************
    Code for Vulkan Graphics and Compute Pipelines
******************************************************/

#pragma once

#include "VulkanCore.h"
#include <vulkan/vulkan.h>

class VulkanDevice;

struct VulkanGraphicsPipelineStateDesc {
    /* Input Assembly state */
    VkPrimitiveTopology Topology;

    /* Rasterizer */
    VkPolygonMode PolygonMode;
    VkCullModeFlags CullMode;
    float DepthBiasSlopeFactor;
    float DepthBiasConstantFactor;

    /* Depth Stencil */
    VkCompareOp DepthCompareOp;
    VkStencilOpState Front;
    VkStencilOpState Back;
    bool bDepthTestEnable;
    bool bDepthWriteEnable;
    bool bStencilTestEnable;
    bool bDepthBoundsTestEnable;
};

// TODO: Implement PSO cache
class VulkanPipelineStateCache {
public:
    void Load();    /* Load from disk */
    void Save();    /* Saves to disk */
private:
    VkPipelineCache PipelineCache;
};

class VulkanGraphicsPipeline {
public:
    VulkanGraphicsPipeline(VulkanDevice* InDevice);

private:
    void CreateGraphicsPipeline();

private:
    VulkanDevice* Device;

    VkPipeline          Pipeline;
    /* descriptor set layouts + push constant ranges */
    VkPipelineLayout    PipelineLayout;

    // Shader modules per Pipeline shader stage
    VkShaderModule ShaderStageModules[ShaderStage::Num];

    VulkanGraphicsPipelineStateDesc Desc;
};

class VulkanComputePipeline {
public:
    VulkanComputePipeline(VulkanDevice* InDevice);

private:
    void CreateComputePipeline();

private:
    VulkanDevice*       Device;

    VkPipeline          Pipeline;
    VkPipelineLayout    PipelineLayout;

    // Compute shader bindings
    VkDescriptorSet         DescriptorSet; 
    VkDescriptorSetLayout   DescriptorSetLayout; /* binding layout */

    VkShaderModule ComputeShaderModule;
};