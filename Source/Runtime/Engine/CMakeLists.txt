#----------------------------------
# Core Library
#----------------------------------

add_library(Engine STATIC
    Source/Engine.cpp
)

#----------------------------------
# Additional libraries
#----------------------------------

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
target_include_directories(Engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)

target_link_libraries(Engine PUBLIC Core)
