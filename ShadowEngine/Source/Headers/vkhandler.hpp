#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "../../enginestructs.hpp"

namespace ShadowEngine {
    class VkHandler {
    public:
        static void CreateInstance();
        static void PickPhysicalDevice();
        static void Cleanup();
        static void CreateSurface(GLFWwindow*);
        static void CreateLogicalDevice();

    private:
        static VkInstance Instance;
        static VkPhysicalDevice PhysicalDevice;
        static VkDevice Device;
        static VkQueue GraphicsQueue;
        static VkQueue PresentQueue;
        static VkSurfaceKHR Surface;

        static bool IsDeviceSuitable(VkPhysicalDevice);
        static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    };
}
