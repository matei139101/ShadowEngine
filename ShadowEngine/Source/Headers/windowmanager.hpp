#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace ShadowEngine {
	class WindowManager {
	public:
		static GLFWwindow* Window;

		static void InitWindow(int h = 400, int w = 600, std::string name = "Default");
		static void Clean();
		static bool ShouldClose() { return glfwWindowShouldClose(Window); }
	};
}