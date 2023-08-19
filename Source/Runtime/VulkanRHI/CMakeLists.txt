#----------------------------------
# Demo Application
#----------------------------------

add_library(VulkanRHI STATIC
    Source/VulkanLoader.cpp
    Source/VulkanDevice.cpp
    Source/VulkanPipeline.cpp
    Source/VulkanRHI.cpp
    Source/VulkanCommandBuffer.cpp
    Source/VulkanDescriptorSet.cpp
    Source/VulkanResource.cpp
    Source/VulkanSwapchain.cpp
    Source/Linux/VulkanLinux.cpp
)

target_include_directories(VulkanRHI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
target_link_libraries(VulkanRHI Core)

#----------------------------------
# Platform-specific configurations
#----------------------------------

if (UNIX)
    target_link_libraries(VulkanRHI dl)
    target_include_directories(VulkanRHI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source/Linux)
elseif (WIN32)

endif()
