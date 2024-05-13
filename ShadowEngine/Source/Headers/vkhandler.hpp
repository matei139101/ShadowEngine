#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "../../enginestructs.hpp"

namespace ShadowEngine {
    class VkHandler {
    public:
        void CreateInstance();
        void PickPhysicalDevice();
        void Cleanup();
        void CreateSurface(GLFWwindow*);
        void CreateLogicalDevice();

    private:
        VkInstance Instance = nullptr;
        VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
        VkDevice Device = nullptr;
        VkQueue GraphicsQueue = nullptr;
        VkQueue PresentQueue = nullptr;
        VkSurfaceKHR Surface = nullptr;

        bool IsDeviceSuitable(VkPhysicalDevice);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    };
}
