cmake_minimum_required(VERSION 3.4.1)

project(vulkan-demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(Source)
