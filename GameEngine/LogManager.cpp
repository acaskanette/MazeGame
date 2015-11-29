#include "LogManager.h"

#include <SDL/SDL.h>
#include <ctime>
#include <sstream>

LogManager* LogManager::theInstance = nullptr;

LogManager::LogManager() {
	out = nullptr;
	logName = "log.log";
	severity = LogLevel::ERROR;
	ignoreLowSeverity = false;
}

LogManager::~LogManager() {
	close();
}

LogManager& LogManager::getInstance() {
	if (theInstance == nullptr)
		theInstance = new LogManager();

	return *theInstance;
}

void LogManager::open(std::string& _fileName) {
	close();
	out = new std::ofstream(_fileName.c_str());
	severity = LogLevel::ERROR;
}

void LogManager::close() {
	if (out) {
		out->close();
		delete out;
		out = nullptr;
	}
}

void LogManager::log(LogLevel _severity, std::string _msg, bool _consolePrinting) {
	if (ignoreLowSeverity && (_severity < severity))
		return;

	if (!out)
		open(logName);

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

void LogManager::setSeverity(LogLevel _severity) {
	severity = _severity;
}

LogLevel LogManager::getSeverity() {
	return severity;
}

void LogManager::setIgnoreSeverity(bool _ignore) {
	ignoreLowSeverity = _ignore;
}

bool LogManager::isLowSeverityIgnored() {
	return ignoreLowSeverity;
}

void LogManager::logError(std::string _msg) {
	log(LogLevel::ERROR, _msg);
}

void LogManager::logWarning(std::string _msg) {
	log(LogLevel::WARN, _msg);
}

void LogManager::logTrace(std::string _msg) {
	log(LogLevel::TRACE, _msg);
}

void LogManager::logInfo(std::string _msg) {
	log(LogLevel::INFO, _msg);
}

void LogManager::logFatal(std::string _msg) {
	log(LogLevel::FATAL, _msg);
	log(LogLevel::FATAL, "Shutting down.");

	SDL_Quit();
	exit(1);
}