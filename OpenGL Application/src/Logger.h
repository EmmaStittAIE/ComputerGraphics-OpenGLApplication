#pragma once

#include <string>
#include <initializer_list>

enum LogType
{
	Info,
	Warning,
	Error
};

namespace Logger
{
	extern void Log(std::initializer_list<std::string> messageText, LogType type);
	extern void LogInfo(std::string infoText);
	extern void LogWarning(std::string warningText);
	extern void LogError(std::string errorText);
}