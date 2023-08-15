#----------------------------------
# Demo Application
#----------------------------------

add_executable(vulkan-demo
  Entry.cpp
)

#----------------------------------
# Additional libraries
#----------------------------------

target_link_libraries(vulkan-demo Engine)
