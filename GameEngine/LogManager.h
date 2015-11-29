#pragma once
#include <fstream>
#include <string>

enum class LogLevel { NUL = 0, INFO, TRACE, WARN, ERROR, FATAL };

class LogManager {
public:
	std::string logName;

	static LogManager& getInstance(); // Singleton class is accessed and constructed by getInstance
	~LogManager();

	void open(std::string& fileName);
	void close();

	void setSeverity(LogLevel _severity);
	LogLevel getSeverity();
	void setIgnoreSeverity(bool _ignore);
	bool isLowSeverityIgnored();

	void log(LogLevel _severity, std::string _msg, bool _consolePrinting = true);
	void logError(std::string _msg);
	void logWarning(std::string _msg);
	void logTrace(std::string _msg);
	void logInfo(std::string _msg);
	void logFatal(std::string _msg);
private:
	static LogManager* theInstance;
	std::ofstream* out;
	LogLevel severity;
	bool ignoreLowSeverity;

	LogManager(); // Private constructor to indicate singleton
};