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

		void initWindow() {
			WindowManager::InitWindow(720, 1280, "Vulkan Main Window");
		}

		void initVulkan() {
			VkHandler::CreateInstance();
		}

		void mainLoop() {
			while (!WindowManager::ShouldClose()) {
				glfwPollEvents();
			}
		}

		void cleanup() {
			VkHandler::Cleanup();
			WindowManager::Clean();
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