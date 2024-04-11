#pragma once
#include "../Headers/globalenums.hpp"

namespace ShadowEngine {
    class ConsoleDebugger {
    public:
        static DebugLevelEnum LoggingLevel;

        static void ConsoleWrite(DebugLevelEnum, const char*);
    };
}