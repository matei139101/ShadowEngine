#pragma once
#include <list>
#include <fstream>
#include <iostream>
#include <chrono>
#include <format>

#include "../Headers/engineenums.hpp"

namespace ShadowEngine {
    class ConsoleDebugger {
    public:
        static std::list<const char*> LoggedData;
        static void Log(DebugLevelEnum, const char*);
        static void SaveLog();
    private:
        static const std::string GetTimeStamp();
        static const std::string LevelToString(const DebugLevelEnum);
    };
}