#pragma once
#include <vulkan/vulkan.h>
#include "../../enginestructs.hpp"

namespace ShadowEngine {
    class VkHandler {
    public:
        static void CreateInstance();
        static void PickPhysicalDevice();
        static void CreateLogicalDevice();
        static void Cleanup();
    private:
        static VkInstance Instance;
        static VkPhysicalDevice PhysicalDevice;
        static VkDevice Device;

        static bool IsDeviceSuitable(VkPhysicalDevice);
        static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    };
}
