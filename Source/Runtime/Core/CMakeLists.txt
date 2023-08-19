#----------------------------------
# Core Library
#----------------------------------

add_library(Core STATIC
    Source/Linux/LinuxApplication.cpp
    Source/Linux/LinuxWindow.cpp
    Source/Linux/LinuxPlatform.cpp
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)

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
