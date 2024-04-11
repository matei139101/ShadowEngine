#pragma once
#include "../Headers/globalenums.hpp"

namespace ShadowEngine {
    class ConsoleDebugger {
    public:
        static DebugLevelEnum LoggingLevel;

        ConsoleDebugger();

        static void ConsoleWrite(DebugLevelEnum, const char*);
    };
}