#include "../Headers/consoledebugger.hpp"
#include "../../engineoptions.hpp"

#include <iostream>


namespace ShadowEngine {
	void ConsoleDebugger::ConsoleWrite(const DebugLevelEnum level, const char* message) {
		if (level <= EngineOptions::DebugLevel) {
			std::string levelAnnotation = "";

			for (int i = 0; i <= level; i++) {
				levelAnnotation += "-";
			}

			std::cout << levelAnnotation << message << '\n';
		}
	}
}
