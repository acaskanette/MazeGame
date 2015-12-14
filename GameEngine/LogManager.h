#pragma once
#include <fstream>
#include <string>

enum class LogLevel { NUL = 0, INFO, TRACE, WARN, ERROR, FATAL };

class LogManager {
public:
	static LogManager* GetInstance(); // Singleton class is accessed and constructed by getInstance
	void DestroyLogManager(LogManager*& rmPtr);

	std::string logName;

	void Open(std::string& fileName);
	void Close();

	void SetSeverity(LogLevel _severity);
	LogLevel GetSeverity();
	void SetIgnoreSeverity(bool _ignore);
	bool IsLowSeverityIgnored();

	void Log(LogLevel _severity, std::string _msg, bool _consolePrinting = true);
	void LogError(std::string _msg);
	void LogWarning(std::string _msg);
	void LogTrace(std::string _msg);
	void LogInfo(std::string _msg);
	void LogFatal(std::string _msg);
private:
	static LogManager* instance;

	std::ofstream* out;
	LogLevel severity;
	bool ignoreLowSeverity;

	LogManager(); // Private constructor to indicate singleton
	~LogManager();
};