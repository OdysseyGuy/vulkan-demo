#include "VulkanPipeline.h"
#include "VulkanCore.h"
#include "VulkanDevice.h"

VulkanGraphicsPipeline::VulkanGraphicsPipeline(VulkanDevice *inDevice)
    : device(inDevice)
    , pipeline(VK_NULL_HANDLE)
{
}

VkShaderStageFlagBits ShaderStageToVulkanShaderStage(ShaderStage stage)
{
    switch (stage) {
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

void VulkanGraphicsPipeline::CreateGraphicsPipeline()
{
    // Graphics Pipeline
    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .layout = pipelineLayout,
    };

    // Viewport
    VkPipelineViewportStateCreateInfo viewportSateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1,
    };

    graphicsPipelineCreateInfo.pViewportState = &viewportSateCreateInfo;

    // Shader Stages
    VkPipelineShaderStageCreateInfo shaderStages[ShaderStage::Num];
    graphicsPipelineCreateInfo.stageCount = 0;
    graphicsPipelineCreateInfo.pStages = shaderStages;

    for (int32_t stageIndex = 0; stageIndex < ShaderStage::Num; ++stageIndex) {
        if (!shaderStageModules[stageIndex]) {
            continue; // we do not have any shader for this stage
        }

        const ShaderStage CurrentStage = (ShaderStage)stageIndex;

        shaderStages[stageIndex].sType =
            VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStages[stageIndex].stage =
            ShaderStageToVulkanShaderStage(CurrentStage);
        shaderStages[stageIndex].module = shaderStageModules[stageIndex];
        shaderStages[stageIndex].pName = "main";

        graphicsPipelineCreateInfo.stageCount++;
    }

    // Input Assembly
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = desc.topology,
    };

    graphicsPipelineCreateInfo.pInputAssemblyState =
        &inputAssemblyStateCreateInfo;

    // Rasterization
    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .polygonMode = desc.polygonMode,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable =
            desc.depthBiasConstantFactor != 0.0f ? VK_TRUE : VK_FALSE,
        .depthBiasConstantFactor = desc.depthBiasConstantFactor,
        .depthBiasSlopeFactor = desc.depthBiasSlopeFactor,
    };

    graphicsPipelineCreateInfo.pRasterizationState =
        &rasterizationStateCreateInfo;

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
    };

    // VK_CALL(vkCreatePipelineLayout());

    // Depth Stencil
    VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable = desc.depthTestEnable,
        .depthWriteEnable = desc.depthWriteEnable,
        .depthCompareOp = desc.depthCompareOp,
        .depthBoundsTestEnable = desc.depthBoundsTestEnable,
        .stencilTestEnable = desc.stencilTestEnable,
        .front = desc.front,
        .back = desc.back,
    };

    graphicsPipelineCreateInfo.pDepthStencilState =
        &depthStencilStateCreateInfo;

    VK_CALL(vkCreateGraphicsPipelines(device->GetLogicalDeviceHandle(), nullptr,
                                      1, &graphicsPipelineCreateInfo, nullptr,
                                      &pipeline));
}

VulkanComputePipeline::VulkanComputePipeline(VulkanDevice *inDevice)
    : device(inDevice)
    , pipeline(VK_NULL_HANDLE)
{
}

void VulkanComputePipeline::CreateComputePipeline()
{
    VkComputePipelineCreateInfo computePipelineCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .stage = {.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
                  .stage = VK_SHADER_STAGE_COMPUTE_BIT,
                  .module = computeShaderModule,
                  .pName = "main"},
    };

    // Descriptor Sets and Push Constant Ranges

    VK_CALL(vkCreateComputePipelines(device->GetLogicalDeviceHandle(), nullptr,
                                     1, &computePipelineCreateInfo, nullptr,
                                     &pipeline));
}