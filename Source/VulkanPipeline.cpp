#include "VulkanCore.h"
#include "VulkanPipeline.h"
#include "VulkanDevice.h"

VulkanGraphicsPipeline::VulkanGraphicsPipeline(VulkanDevice* InDevice)
    : Device(InDevice)
    , Pipeline(VK_NULL_HANDLE)
{
}

VkShaderStageFlagBits ShaderStageToVulkanShaderStage(ShaderStage Stage) {
    switch (Stage)
    {
    case ShaderStage::Vertex:
        return VK_SHADER_STAGE_VERTEX_BIT;

    case ShaderStage::Fragment:
        return VK_SHADER_STAGE_FRAGMENT_BIT;

    case ShaderStage::Geometry:
        return VK_SHADER_STAGE_GEOMETRY_BIT;
    
    default:
        assert(0);
    }
}

void VulkanGraphicsPipeline::CreateGraphicsPipeline() {
    // Graphics Pipeline
    VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .layout = PipelineLayout,
    };

    // Viewport
    VkPipelineViewportStateCreateInfo ViewportSateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1,
    };

    GraphicsPipelineCreateInfo.pViewportState = &ViewportSateCreateInfo;

    // Shader Stages
    VkPipelineShaderStageCreateInfo ShaderStages[ShaderStage::Num];
    GraphicsPipelineCreateInfo.stageCount = 0;
    GraphicsPipelineCreateInfo.pStages = ShaderStages;

    for (int32_t StageIndex = 0; StageIndex < ShaderStage::Num; ++StageIndex) {
        if (!ShaderStageModules[StageIndex]) {
            continue; // we do not have any shader for this stage
        }

        const ShaderStage CurrentStage = (ShaderStage)StageIndex;

        ShaderStages[StageIndex].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ShaderStages[StageIndex].stage = ShaderStageToVulkanShaderStage(CurrentStage);
        ShaderStages[StageIndex].module = ShaderStageModules[StageIndex];
        ShaderStages[StageIndex].pName = "main";

        GraphicsPipelineCreateInfo.stageCount++;
    }

    // Input Assembly
    VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = Desc.Topology,
    };

    GraphicsPipelineCreateInfo.pInputAssemblyState = &InputAssemblyStateCreateInfo;

    // Rasterization
    VkPipelineRasterizationStateCreateInfo RasterizationStateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .polygonMode = Desc.PolygonMode,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable = Desc.DepthBiasConstantFactor != 0.0f ? VK_TRUE : VK_FALSE,
        .depthBiasConstantFactor = Desc.DepthBiasConstantFactor,
        .depthBiasSlopeFactor = Desc.DepthBiasSlopeFactor,
    };

    GraphicsPipelineCreateInfo.pRasterizationState = &RasterizationStateCreateInfo;

    VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
    };

    // VK_CALL(vkCreatePipelineLayout());

    // Depth Stencil
    VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable = Desc.bDepthTestEnable,
        .depthWriteEnable = Desc.bDepthWriteEnable,
        .depthCompareOp = Desc.DepthCompareOp,
        .depthBoundsTestEnable = Desc.bDepthBoundsTestEnable,
        .stencilTestEnable = Desc.bStencilTestEnable,
        .front = Desc.Front,
        .back = Desc.Back,
    };

    GraphicsPipelineCreateInfo.pDepthStencilState = &DepthStencilStateCreateInfo;

    VK_CALL(vkCreateGraphicsPipelines(
        Device->GetLogicalDeviceHandle(), nullptr, 1, &GraphicsPipelineCreateInfo,
        nullptr, &Pipeline));
}

VulkanComputePipeline::VulkanComputePipeline(VulkanDevice* InDevice)
    : Device(InDevice)
    , Pipeline(VK_NULL_HANDLE)
{
}

void VulkanComputePipeline::CreateComputePipeline() {
    VkComputePipelineCreateInfo ComputePipelineCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .stage = {
            .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_COMPUTE_BIT,
            .module = ComputeShaderModule,
            .pName = "main"
        },
    };

    // Descriptor Sets and Push Constant Ranges

    VK_CALL(vkCreateComputePipelines(
        Device->GetLogicalDeviceHandle(), nullptr, 1, &ComputePipelineCreateInfo,
        nullptr, &Pipeline));
}