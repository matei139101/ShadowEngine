#include "../Headers/windowmanager.hpp"

namespace ShadowEngine {

	void WindowManager::Clean() {
		//Cleansup after glfw and window
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowManager::InitWindow(int h, int w, std::string name) {
		//Initiates glfw
		glfwInit();

		//Tells the window to not use openGL
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		//Creates the window
		window = glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr);
	}
}