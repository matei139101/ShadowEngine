#pragma once
#include "../Headers/engineenums.hpp"

namespace ShadowEngine {
    class ConsoleDebugger {
    public:
        static void ConsoleWrite(DebugLevelEnum, const char*);
    };
}