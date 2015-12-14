#include "LogManager.h"
#include <SDL/SDL.h>
#include <ctime>
#include <sstream>

LogManager* LogManager::instance = nullptr;

LogManager* LogManager::GetInstance() {
	if (instance == nullptr)
		instance = new LogManager();

	return instance;
}

void LogManager::DestroyLogManager(LogManager*& logManagerPointer) {
	if (instance) {
		delete instance;
		instance = nullptr;
		logManagerPointer = nullptr;
	}
}

LogManager::LogManager() {
	out = nullptr;
	logName = "log.log";
	severity = LogLevel::ERROR;
	ignoreLowSeverity = false;
}

LogManager::~LogManager() {
	Close();
}

void LogManager::Open(std::string& _fileName) {
	Close();
	out = new std::ofstream(_fileName.c_str());
	severity = LogLevel::ERROR;
}

void LogManager::Close() {
	if (out) {
		out->close();
		delete out;
		out = nullptr;
	}
}

void LogManager::Log(LogLevel _severity, std::string _msg, bool _consolePrinting) {
	if (ignoreLowSeverity && (_severity < severity))
		return;

	if (!out)
		Open(logName);

	time_t t = time(0); // Get time
	struct tm now;
	localtime_s(&now, &t);

	std::stringstream ss;
	ss << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << " - " << _msg << "\n";

	(*out) << ss.str();
	out->flush();

	if (_consolePrinting)
		printf(ss.str().c_str());
}

void LogManager::SetSeverity(LogLevel _severity) {
	severity = _severity;
}

LogLevel LogManager::GetSeverity() {
	return severity;
}

void LogManager::SetIgnoreSeverity(bool _ignore) {
	ignoreLowSeverity = _ignore;
}

bool LogManager::IsLowSeverityIgnored() {
	return ignoreLowSeverity;
}

void LogManager::LogError(std::string _msg) {
	Log(LogLevel::ERROR, _msg);
}

void LogManager::LogWarning(std::string _msg) {
	Log(LogLevel::WARN, _msg);
}

void LogManager::LogTrace(std::string _msg) {
	Log(LogLevel::TRACE, _msg);
}

void LogManager::LogInfo(std::string _msg) {
	Log(LogLevel::INFO, _msg);
}

void LogManager::LogFatal(std::string _msg) {
	Log(LogLevel::FATAL, _msg);
	Log(LogLevel::FATAL, "Shutting down.");

	SDL_Quit();
	exit(1);
}