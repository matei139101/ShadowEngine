#pragma once
#include <optional>
#include <vulkan/vulkan.h>

namespace ShadowEngine {
    class VkHandler {
    public:
        static void CreateInstance();
        static void Cleanup();
        static void PickPhysicalDevice();
    private:
        struct QueueFamilyIndices {
            std::optional<uint32_t> GraphicsFamily;

            bool isComplete() {
                return GraphicsFamily.has_value();
            }
        };

        static VkInstance Instance;
        static bool IsDeviceSuitable(VkPhysicalDevice);
        static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    };
}