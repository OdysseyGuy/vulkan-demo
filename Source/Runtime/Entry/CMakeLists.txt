#----------------------------------
# Demo Application
#----------------------------------

add_executable(vulkan-demo
  Source/Entry.cpp
)

#----------------------------------
# Additional libraries
#----------------------------------

target_link_libraries(vulkan-demo Engine)
