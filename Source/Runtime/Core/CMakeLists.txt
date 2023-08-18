#----------------------------------
# Core Library
#----------------------------------

add_library(Core STATIC
    Linux/LinuxApplication.cpp
    Linux/LinuxWindow.cpp
)

#----------------------------------
# Additional libraries
#----------------------------------

target_include_directories(Core PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))

#----------------------------------
# Platform-specific configurations
#----------------------------------

if (UNIX)
    find_package(SDL2 REQUIRED)
    target_include_directories(Core PUBLIC ${SDL2_INCLUDE_DIRS})
    target_link_libraries(Core ${SDL2_LIBRARIES})
    target_link_libraries(Core dl) # for dlopen()
elseif (WIN32)

endif()
