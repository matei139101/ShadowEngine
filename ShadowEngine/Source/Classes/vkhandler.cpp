#include "../Headers/vkhandler.hpp"
#include "../Headers/consoledebugger.hpp"
#include "../../enginestructs.hpp"

#include <optional>
#include <set>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

#include "../Headers/windowmanager.hpp"

namespace ShadowEngine {
	VkInstance VkHandler::Instance;
	VkPhysicalDevice VkHandler::PhysicalDevice = VK_NULL_HANDLE;
	VkDevice VkHandler::Device;
	VkQueue VkHandler::GraphicsQueue;
	VkQueue VkHandler::PresentQueue;
	VkSurfaceKHR VkHandler::Surface;

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

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(Instance, &deviceCount, nullptr);

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(Instance, &deviceCount, devices.data());

		if (deviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		for (const auto& device : devices) {
			if (IsDeviceSuitable(device)) {
				PhysicalDevice = device;
				break;
			}
		}

		if (PhysicalDevice == VK_NULL_HANDLE) {
			throw std::runtime_error("failed to find a suitable GPU!");
		}

		ConsoleDebugger::ConsoleWrite(Medium, "Finished picking GPU");
	}

	bool VkHandler::IsDeviceSuitable(const VkPhysicalDevice device) {
		QueueFamilyIndices indices = FindQueueFamilies(device);

		return indices.isComplete();
	}

	QueueFamilyIndices VkHandler::FindQueueFamilies(const VkPhysicalDevice device) {
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

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, Surface, &presentSupport);

			if (presentSupport) {
				indices.PresentFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}

	void VkHandler::CreateLogicalDevice() {
		QueueFamilyIndices indices = FindQueueFamilies(PhysicalDevice);
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };
		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.GraphicsFamily.value();
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		if (vkCreateDevice(PhysicalDevice, &createInfo, nullptr, &Device) != VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}

		vkGetDeviceQueue(Device, indices.GraphicsFamily.value(), 0, &GraphicsQueue);
		vkGetDeviceQueue(Device, indices.PresentFamily.value(), 0, &PresentQueue);
	}

	void VkHandler::Cleanup() {
		ConsoleDebugger::ConsoleWrite(High, "Cleaning up Vulkan");

		vkDestroyDevice(Device, nullptr);
		vkDestroySurfaceKHR(Instance, Surface, nullptr);
		vkDestroyInstance(Instance, nullptr);

		ConsoleDebugger::ConsoleWrite(Medium, "Finished cleaning up Vulkan");
	}

	void VkHandler::CreateSurface() {
		if (glfwCreateWindowSurface(Instance, WindowManager::Window, nullptr, &Surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}
}
