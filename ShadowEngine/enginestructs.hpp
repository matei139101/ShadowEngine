#pragma once
#include <optional>
#include <vector>

namespace ShadowEngine {
	struct SystemInfo {
		std::vector<VkPhysicalDevice> GraphicalProcessors;
	};

    struct QueueFamilyIndices {
        std::optional<uint32_t> GraphicsFamily;

        bool isComplete() {
            return GraphicsFamily.has_value();
        }
    };
};

