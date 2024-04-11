#pragma once
#include <optional>
#include <vector>

namespace ShadowEngine {
    struct QueueFamilyIndices {
        std::optional<uint32_t> GraphicsFamily;

        bool isComplete() {
            return GraphicsFamily.has_value();
        }
    };
};

