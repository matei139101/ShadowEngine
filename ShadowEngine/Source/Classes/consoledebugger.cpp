#include "../Headers/consoledebugger.hpp"
#include "../../engineoptions.hpp"

#include <iostream>


namespace ShadowEngine {
	std::list<const char*> ConsoleDebugger::LoggedData;

	void ConsoleDebugger::Log(const DebugLevelEnum level, const char* message) {
		if (level <= EngineOptions::DebugLevel) {
			std::string fullMessage = GetTimeStamp() + " | ";
			fullMessage += std::string("DebugLevel: ") + LevelToString(level) + " | ";
			fullMessage += std::string("Message: ") + message + '\n';
			LoggedData.push_front(fullMessage.c_str());
			std::cout << fullMessage;
		}
	}

	void ConsoleDebugger::SaveLog() {
		std::ofstream logFile;
		std::string fileName = ConsoleDebugger::GetTimeStamp();
		fileName += ".log";

		logFile.open(fileName);

		for (std::string log: LoggedData) {
			logFile << log << "\n";
		}

		logFile.close();
	}

	std::string ConsoleDebugger::GetTimeStamp() {
		const std::chrono::time_point timestamp = std::chrono::system_clock::now();
		const std::string timeStamp = std::format("{:%Y:%m:%d:%H:%M}", timestamp);

		return timeStamp;
	}

	std::string ConsoleDebugger::LevelToString(const DebugLevelEnum level) {
		///TO-DO I severely hate the way this looks and works... but it does.
		switch (level) {
		case Low:
			return "Low       ";
		case Medium:
			return "Medium    ";
		case High:
			return "High      ";
		default:
			return "Unknown   ";
		}
	}
}
