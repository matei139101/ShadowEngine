#include "../Headers/vkhandler.hpp"

#include <optional>

#include "../Headers/consoledebugger.hpp"
#include "../../enginestructs.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

namespace ShadowEngine {
	VkInstance VkHandler::Instance;

	void VkHandler::CreateInstance() {
		ConsoleDebugger::ConsoleWrite(High, "Initializing Vulkan");

		uint32_t glfwExtensionCount = 0;
		uint32_t extensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "ShadowEngine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "ShadowEngine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_3;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &Instance);

		if (vkCreateInstance(&createInfo, nullptr, &Instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}

		ConsoleDebugger::ConsoleWrite(Medium, "Finished initializing Vulkan");
	}

	void VkHandler::PickPhysicalDevice()
	{
		ConsoleDebugger::ConsoleWrite(High, "Picking GPU");

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		uint32_t deviceCount = 0;
		std::vector<VkPhysicalDevice> devices(deviceCount);

		vkEnumeratePhysicalDevices(Instance, &deviceCount, devices.data());

		if (deviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		for (const auto& device : devices) {
			if (IsDeviceSuitable(device)) {
				physicalDevice = device;
				break;
			}
		}

		if (physicalDevice == VK_NULL_HANDLE) {
			throw std::runtime_error("failed to find a suitable GPU!");
		}

		ConsoleDebugger::ConsoleWrite(Medium, "Finished picking GPU");
	}

	void VkHandler::Cleanup() {
		ConsoleDebugger::ConsoleWrite(High, "Cleaning up Vulkan");

		vkDestroyInstance(Instance, nullptr);

		ConsoleDebugger::ConsoleWrite(Medium, "Finished cleaning up Vulkan");
	}

	bool VkHandler::IsDeviceSuitable(const VkPhysicalDevice device) {
		QueueFamilyIndices indices = FindQueueFamilies(device);

		return indices.isComplete();
	}

	VkHandler::QueueFamilyIndices VkHandler::FindQueueFamilies(VkPhysicalDevice device) {
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.GraphicsFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}
}
