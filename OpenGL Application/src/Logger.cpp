#include "Logger.h"

#include <iostream>
#include <format>
#include <chrono>
using namespace std::chrono;

void Logger::Log(std::initializer_list<std::string> messageText, LogType type)
{
	std::string concatMessage;
	for (std::string messagePart : messageText)
	{
		concatMessage += messagePart;
	}

	switch (type)
	{
	case Info:
		concatMessage = "Info: " + concatMessage;
		break;
	case Warning:
		concatMessage = "Warning: " + concatMessage;
		break;
	case Error:
		concatMessage = "Error: " + concatMessage;
		break;
	default:
		break;
	}

	// ugh i hate chrono
	std::string timeString = "[" +
							 std::format("{:%T}", zoned_time{current_zone(), system_clock::now()}).erase(8, std::string::npos)
							 + "] ";

	std::cout << timeString << concatMessage << std::endl;
}

void Logger::LogInfo(std::string infoText)
{
	std::cout << "INFO: " << infoText << std::endl;
}

void Logger::LogWarning(std::string warningText)
{
	std::cout << "WARN: " << warningText << std::endl;
}

void Logger::LogError(std::string errorText)
{
	std::cout << "ERROR: " << errorText << std::endl;

	std::string string = "bvkskljsbv: ";
}
