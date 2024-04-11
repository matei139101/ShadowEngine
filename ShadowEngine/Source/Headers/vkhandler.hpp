#pragma once
#include <vulkan/vulkan.h>

namespace ShadowEngine {
    class VkHandler {
    public:
        static void CreateInstance();
        static void Cleanup();
    private:
        static VkInstance Instance;
    };
}