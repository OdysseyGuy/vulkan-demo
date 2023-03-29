#----------------------------------
# Demo Application
#----------------------------------

add_executable( vulkan-demo
  main.cpp
  VulkanLoader.cpp
  VulkanDevice.cpp
  VulkanPipeline.cpp
  VulkanRHI.cpp
  VulkanCommandBuffer.cpp
  VulkanDescriptorSet.cpp
  VulkanResource.cpp
)

#----------------------------------
# Additional libraries
#----------------------------------

target_link_libraries(vulkan-demo dl)
