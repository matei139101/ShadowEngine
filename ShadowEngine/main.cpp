#include <iostream>
#include <cstdlib>

#include "Source/Headers/windowmanager.hpp"
#include "Source/Headers/vkhandler.hpp"
#include "Source/Headers/consoledebugger.hpp"

namespace ShadowEngine {

	class ShadowEngine {
	public:
		void Run() {
			//Application core
			InitWindow();
			InitVulkan();
			MainLoop();
			Cleanup();
		}

	private:
		WindowManager WindowManager;
		VkHandler VkHandler;

		void InitWindow() {
			WindowManager.InitWindow(720, 1280, "Vulkan Main Window");
		}

		void InitVulkan() {
			VkHandler.CreateInstance();
			VkHandler.CreateSurface(WindowManager.Window);
			VkHandler.PickPhysicalDevice();
			VkHandler.CreateLogicalDevice();
		}

		void MainLoop() {
			while (!WindowManager.ShouldClose()) {
				glfwPollEvents();
			}
		}

		void Cleanup() {
			VkHandler.Cleanup();
			WindowManager.Clean();
			ConsoleDebugger::SaveLog();
		}
	};
}

int main() {
	ShadowEngine::ShadowEngine app;

	try {
		app.Run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}