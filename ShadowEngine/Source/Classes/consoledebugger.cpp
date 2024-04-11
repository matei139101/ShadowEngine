#include "../Headers/consoledebugger.hpp"

#include <iostream>

namespace ShadowEngine {
	DebugLevelEnum ConsoleDebugger::LoggingLevel = High;

	void ConsoleDebugger::ConsoleWrite(const DebugLevelEnum level, const char* message) {
		if (level <= LoggingLevel) {
			std::cout << message << '\n';
		}
	}
}