#include "../Headers/vkhandler.hpp"
#include "../Headers/consoledebugger.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

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

	void VkHandler::Cleanup() {
		ConsoleDebugger::ConsoleWrite(High, "Cleaning up Vulkan");

		vkDestroyInstance(Instance, nullptr);

		ConsoleDebugger::ConsoleWrite(Medium, "Finished cleaning up Vulkan");
	}
}