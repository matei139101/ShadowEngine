#include "../Headers/windowmanager.hpp"
#include "../Headers/consoledebugger.hpp"

namespace ShadowEngine {
	void WindowManager::Clean() {
		glfwDestroyWindow(Window);
		glfwTerminate();
	}

	void WindowManager::InitWindow(const int h, const int w, const std::string& name) {
		ConsoleDebugger::ConsoleWrite(High, "Initializing window");
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		Window = glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr);
		ConsoleDebugger::ConsoleWrite(Medium, "Finished initializing window");
	}
}
