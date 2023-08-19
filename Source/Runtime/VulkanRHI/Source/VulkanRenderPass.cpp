#include <vector>
#include "VulkanRenderPass.h"
#include "VulkanDevice.h"

static bool SupportsSeprateDepthStencil()
{
    return false;
}

VulkanFramebuffer::VulkanFramebuffer(VulkanDevice *device, const VulkanRenderTargetLayout *layout,
                                     const VulkanRenderPass *renderPass)
{
}

VulkanFramebuffer::~VulkanFramebuffer()
{
}

VulkanRenderPass::VulkanRenderPass(VulkanDevice *inDevice, const VulkanRenderTargetLayout &inLayout)
    : layout(inLayout)
    , device(inDevice)
{
    uint32_t numSubpasses = 0;
    uint32_t numDependencies = 0;

    bool hasDepthStencilAttachmentRef = layout.HasDepthStencil();
    bool deferredShadingSubpass;

    std::vector<VkAttachmentReference2> colorAttachments;
    VkAttachmentReference2 depthStencilAttachment;          // for depth only
    VkAttachmentReference2 depthStencilAttachmentReference; // for both depth and stencil

    VkSubpassDescription2 subpassDescriptions[4];
    VkSubpassDependency2 subpassDependencies[4];

    VkAttachmentReference2 inputAttachments[8];

    for (uint8_t attachment = 0; attachment < layout.GetNumColorAttachements(); ++attachment) {
        colorAttachments.emplace_back(layout.GetColorAttachmentReferences()[attachment]);
    }

    if (layout.HasDepthStencil()) {
        bool supportsSeparateDepthStencil = SupportsSeprateDepthStencil();
        const VkAttachmentReferenceStencilLayout *stencilReference =
            layout.GetStencilAttachmentReference();

        depthStencilAttachmentReference.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
        depthStencilAttachmentReference.attachment =
            layout.GetDepthAttachmentReference()->attachment;
        depthStencilAttachmentReference.pNext =
            (supportsSeparateDepthStencil and stencilReference and
             stencilReference->stencilLayout != VK_IMAGE_LAYOUT_UNDEFINED)
                ? stencilReference
                : nullptr;
        depthStencilAttachmentReference.layout = layout.GetDepthAttachmentReference()->layout;
        depthStencilAttachmentReference.aspectMask = 0;
    }

    // main pass
    {
        VkSubpassDescription2 &mainpassDesc = subpassDescriptions[numSubpasses++];
        mainpassDesc.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
        mainpassDesc.colorAttachmentCount = colorAttachments.size();
        mainpassDesc.pColorAttachments = colorAttachments.data();
        if (hasDepthStencilAttachmentRef) {
            mainpassDesc.pDepthStencilAttachment = &depthStencilAttachment;
        }
    }

    if (deferredShadingSubpass) {
        depthStencilAttachment.attachment = layout.GetDepthAttachmentReference()->attachment;
        depthStencilAttachment.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        depthStencilAttachment.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

        {
            VkSubpassDescription2 &subpassDesc = subpassDescriptions[numSubpasses++];
            subpassDesc.colorAttachmentCount = colorAttachments.size();
            subpassDesc.pColorAttachments = colorAttachments.data();
            subpassDesc.pDepthStencilAttachment = &depthStencilAttachment;
            subpassDesc.inputAttachmentCount = 1;
            subpassDesc.pInputAttachments = &depthStencilAttachment;

            VkSubpassDependency2 subpassDep = subpassDependencies[numDependencies++];
            subpassDep.srcSubpass = 0;
            subpassDep.dstSubpass = 1;
            subpassDep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                                      VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT |
                                      VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
            subpassDep.dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
            subpassDep.srcAccessMask =
                VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
            subpassDep.dstAccessMask = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
            subpassDep.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
        }

        {
            VkSubpassDescription2 &subpassDesc = subpassDescriptions[numSubpasses++];
            subpassDesc.colorAttachmentCount = 1; // Scene color only
            subpassDesc.pColorAttachments = colorAttachments.data();
            subpassDesc.pDepthStencilAttachment = &depthStencilAttachment;
            subpassDesc.inputAttachmentCount = 1;
            subpassDesc.pInputAttachments = &depthStencilAttachment;

            // Depth as Input0
            inputAttachments[0].attachment = depthStencilAttachment.attachment;
            inputAttachments[0].layout = depthStencilAttachment.layout;
            inputAttachments[0].aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

            // Gbuffer as Input
            uint32_t numColorAttachments = colorAttachments.size();
            for (uint32_t i = 1; i <= numColorAttachments; ++i) {
                inputAttachments[i].attachment = colorAttachments[i - 1].attachment;
                inputAttachments[i].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                inputAttachments[i].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            }

            subpassDesc.inputAttachmentCount = numColorAttachments + 1;
            subpassDesc.pInputAttachments = inputAttachments;

            VkSubpassDependency2 subpassDep = subpassDependencies[numDependencies++];
            subpassDep.srcSubpass = 1;
            subpassDep.dstSubpass = 2;
            subpassDep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            subpassDep.dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
            subpassDep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            subpassDep.dstAccessMask = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
            subpassDep.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
        }
    }

#if 0
    // TODO: See if I need to process the stencil layout with VkAttachmentDescriptionStencilLayout
    std::vector<VkAttachmentDescription2> attachmentDescriptions;

    for (uint8_t attachment = 0; attachment < layout.GetNumAttachmentDescriptions(); ++attachment) {
        if (hasDepthStencilAttachmentRef and attachment == depthStencilAttachment.attachment) {
            VkAttachmentDescription2 desc = layout.GetAttachmentDescriptions()[attachment];
            const VkAttachmentDescriptionStencilLayout *stencilLayout =
                layout.GetStencilDescription();

            attachmentDescriptions.emplace_back(desc);
        } else {
            attachmentDescriptions.emplace_back(layout.GetAttachmentDescriptions()[attachment]);
        }
    }
#endif

    VkRenderPassCreateInfo2 createInfo = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2,
        .attachmentCount = static_cast<uint32_t>(layout.GetNumAttachmentDescriptions()),
        .pAttachments = layout.GetAttachmentDescriptions(),
        .subpassCount = numSubpasses,
        .pSubpasses = subpassDescriptions,
        .dependencyCount = numDependencies,
        .pDependencies = subpassDependencies,
    };

    VkResult result =
        vkCreateRenderPass2(device->GetLogicalDeviceHandle(), &createInfo, nullptr, &renderPass);
}

VulkanRenderPassManager::VulkanRenderPassManager(VulkanDevice *inDevice)
    : device(inDevice)
{
}

VulkanRenderPassManager::~VulkanRenderPassManager()
{
}

void VulkanRenderPassManager::BeginRenderPass(VulkanDevice &device, VulkanCommandBuffer *cmdBuf,
                                              const VulkanRenderTargetLayout &layout,
                                              VulkanRenderPass *renderPass,
                                              VulkanFramebuffer *frameBuf)
{
    // NumRT + Depth
    VkClearColorValue clearColor[8 + 1];
    uint32_t clearColorIndex = 0;

    // TODO:
    uint32_t numColorRenderTargets = 0;

    for (uint32_t i = 0; i < numColorRenderTargets; ++i) {}
}

void VulkanRenderPassManager::EndRenderPass(VulkanCommandBuffer *cmdBuf)
{
}
