#pragma once

#include <unordered_map>
#include <vector>
#include "VulkanLoader.h"

class VulkanDevice;
class VulkanRenderPass;
class VulkanCommandBuffer;

class VulkanRenderTargetLayout
{
public:
    VulkanRenderTargetLayout(VulkanDevice *device);

    inline const VkAttachmentReference2 *GetColorAttachmentReferences() const
    {
        return numColorAttachments > 0 ? colorReferences : nullptr;
    }

    inline const VkAttachmentReference2 *GetDepthAttachmentReference() const
    {
        return hasDepthStencil ? &depthReference : nullptr;
    }

    inline const VkAttachmentReferenceStencilLayout *GetStencilAttachmentReference() const
    {
        return hasDepthStencil ? &stencilReference : nullptr;
    }

    inline const uint8_t GetNumColorAttachements() const
    {
        return numColorAttachments;
    }

    inline const bool HasDepthStencil() const
    {
        return hasDepthStencil;
    }

    inline const uint8_t GetNumAttachmentDescriptions() const
    {
        return numAttachmentDescriptions;
    }

    inline const VkAttachmentDescription2 *GetAttachmentDescriptions() const
    {
        return desc;
    }

    inline const VkAttachmentDescriptionStencilLayout *GetStencilDescription() const
    {
        return hasDepthStencil ? &stencilDesc : nullptr;
    }

private:
    VkAttachmentReference2 colorReferences[1];
    VkAttachmentReference2 depthReference;
    VkAttachmentReferenceStencilLayout stencilReference;

    // one for color attachment, another for depth
    VkAttachmentDescription2 desc[2];
    VkAttachmentDescriptionStencilLayout stencilDesc;

    uint8_t numColorAttachments;
    bool hasDepthStencil;
    uint8_t numInputAttachments;
    uint8_t numAttachmentDescriptions;
};

class VulkanFramebuffer
{
public:
    VulkanFramebuffer(VulkanDevice *device, const VulkanRenderTargetLayout *layout,
                      const VulkanRenderPass *renderPass);
    ~VulkanFramebuffer();

    inline VkFramebuffer GetHandle()
    {
        return framebuffer;
    }

    inline VkRect2D GetRenderArea() const
    {
        return renderArea;
    }

private:
    VkFramebuffer framebuffer;
    VkRect2D renderArea;
};

class VulkanRenderPass
{
public:
    inline const VulkanRenderTargetLayout &GetLayout() const
    {
        return layout;
    }

    inline VkRenderPass GetHandle() const
    {
        return renderPass;
    }

private:
    VulkanRenderPass(VulkanDevice *device, const VulkanRenderTargetLayout &layout);

private:
    VulkanRenderTargetLayout layout;
    VulkanDevice *device;
    VkRenderPass renderPass;
};

class VulkanRenderPassManager
{
public:
    VulkanRenderPassManager(VulkanDevice *device);
    ~VulkanRenderPassManager();

    void BeginRenderPass(VulkanDevice &device, VulkanCommandBuffer *cmdBuf,
                         const VulkanRenderTargetLayout &layout, VulkanRenderPass *renderPass,
                         VulkanFramebuffer *frameBuf);
    void EndRenderPass(VulkanCommandBuffer *cmdBuf);

private:
    VulkanDevice *device;

    std::unordered_map<uint32_t, VulkanRenderPass *> renderPases;
    struct VulkanFramebufferList
    {
        std::vector<VulkanFramebuffer *> framebuffer;
    };
    std::unordered_map<uint32_t, VulkanFramebufferList *> framebuffers;
};
