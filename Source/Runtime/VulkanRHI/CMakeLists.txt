#----------------------------------
# Demo Application
#----------------------------------

add_library(VulkanRHI STATIC
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

target_link_libraries(VulkanRHI dl)
target_include_directories(VulkanRHI PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))
