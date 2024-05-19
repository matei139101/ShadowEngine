#include "../Headers/consoledebugger.hpp"
#include "../../engineoptions.hpp"


namespace ShadowEngine {
	std::list<std::string> ConsoleDebugger::LoggedData;

	void ConsoleDebugger::Log(const DebugLevelEnum level, const char* message) {
		if (level <= EngineOptions::DebugLevel) {
			std::string fullMessage = GetTimeStamp() + " | ";
			fullMessage += std::string("DebugLevel: ") + LevelToString(level) + " | ";
			fullMessage += std::string("Message: ") + message + '\n';
			LoggedData.push_front(fullMessage);
			std::cout << fullMessage;
		}
	}

	void ConsoleDebugger::SaveLog() {
		std::string fileName = "./Logs/" + GetTimeStamp() + ".txt";

		std::ofstream logFile(fileName.c_str());

		if (logFile) {
			for (std::string log : LoggedData) {
				logFile << log;
			}

			logFile.close();
		}
		else {
			std::cout << "The log file couldn't be saved";
		}
		
	}

	std::string ConsoleDebugger::GetTimeStamp() {
		const std::chrono::time_point timestamp = std::chrono::system_clock::now();
		const std::string timeStamp = std::format("{:%Y-%m-%d-%H-%M}", timestamp);

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
