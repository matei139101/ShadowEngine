#pragma once
#include <optional>
#include <vector>

namespace ShadowEngine {
    struct QueueFamilyIndices {
        std::optional<uint32_t> GraphicsFamily;
        std::optional<uint32_t> PresentFamily;

        bool isComplete() {
            return GraphicsFamily.has_value() && PresentFamily.has_value();
        }
    };
};

