#include "VulkanCommandBuffer.h"

void RHIDrawPrimitive(uint32_t numPrimitives, uint32_t numInstances)
{
    VulkanCommandBuffer *cmdBuffer;
    // vkCmdDraw(cmdBuffer->GetHandle());
}

void RHIDrawPrimitiveIndirect(uint32_t numPrimitives, uint32_t numInstances)
{
    VulkanCommandBuffer *cmdBuffer;
    // vkCmdDrawIndirect(cmdBuffer->GetHandle());
}

void RHIDrawIndexedPrimitive(int32_t baseVertexCount, uint32_t firstInstance, uint32_t numVertices,
                             uint32_t startIndex, uint32_t numPrimitives, uint32_t numInstances)
{
    VulkanCommandBuffer *cmdBuffer;
    // vkCmdDrawIndexed(cmdBuffer->GetHandle())
}

void RHIDrawIndexedPrimitiveIndirect(int32_t baseVertexCount, uint32_t firstInstance,
                                     uint32_t numVertices, uint32_t startIndex,
                                     uint32_t numPrimitives, uint32_t numInstances)
{
    VulkanCommandBuffer *cmdBuffer;
    // vkCmdDrawIndexedIndirect(cmdBuffer->GetHandle())
}
