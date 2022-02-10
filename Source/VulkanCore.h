#pragma once

#include <cassert>

#define VK_CALL(VkFunc)             \
    if (VK_SUCCESS != (VkFunc)) {   \
        assert(false);              \
    }

// Vulkan Graphics Pipeline shader stages
enum ShaderStage {
    Vertex = 0,
    Fragment = 1,
    Geometry = 2,
    Num = 3,
};