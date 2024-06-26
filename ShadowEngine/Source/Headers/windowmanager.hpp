#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace ShadowEngine {
	class WindowManager {
	public:
		GLFWwindow* Window = nullptr;

		void InitWindow(int h = 400, int w = 600, const std::string& name = "Default");
		void Clean();
		bool ShouldClose() { return glfwWindowShouldClose(Window); }
	};
}