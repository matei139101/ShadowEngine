#include <iostream>
#include <cstdlib>

#include "Source/Headers/windowmanager.hpp"
#include "Source/Headers/vkhandler.hpp"

namespace ShadowEngine {

	class ShadowEngine {
	public:
		void run() {
			//Application core
			initWindow();
			initVulkan();
			mainLoop();
			cleanup();
		}

	private:
		WindowManager windowManager;
		VKHandler vkHandler;

		void initWindow() {
			windowManager.InitWindow(720, 1280, "Vulkan Main Window");
		}

		void initVulkan() {
			vkHandler.CreateInstance();
		}

		void mainLoop() {
			while (!windowManager.ShouldClose()) {
				glfwPollEvents();
			}
		}

		void cleanup() {
			vkHandler.Cleanup();
			windowManager.Clean();
		}
	};
}

int main() {
	ShadowEngine::ShadowEngine app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}