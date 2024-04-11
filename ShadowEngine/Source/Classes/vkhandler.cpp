#include "../Headers/vkhandler.hpp"
#include "../Headers/consoledebugger.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace ShadowEngine {
	void VKHandler::CreateInstance() {
		ConsoleDebugger::ConsoleWrite(High, "Initializing Vulkan");
		VkApplicationInfo appInfo{};
		VkInstanceCreateInfo createInfo{};

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;
		appInfo.apiVersion = VK_API_VERSION_1_3;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}

		ConsoleDebugger::ConsoleWrite(Low, "Finished initializing Vulkan");
	}

	void VKHandler::Cleanup() {
		vkDestroyInstance(instance, nullptr);
	}
}