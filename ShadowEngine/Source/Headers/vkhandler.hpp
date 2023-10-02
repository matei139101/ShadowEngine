#include <vulkan/vulkan.h>

namespace ShadowEngine {
    class VKHandler {
    public:
        void CreateInstance();
        void Cleanup();
    private:
        VkInstance instance;
    };
}