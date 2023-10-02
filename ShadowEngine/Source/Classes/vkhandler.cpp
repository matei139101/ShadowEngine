#include "../Headers/vkhandler.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

namespace ShadowEngine {
	void VKHandler::CreateInstance() {
		VkApplicationInfo appInfo{};

		VkInstanceCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}

		std::cout << "created VK instance";
	}

	void VKHandler::Cleanup() {
		vkDestroyInstance(instance, nullptr);
	}
}