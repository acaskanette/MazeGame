#include "Clock.h"

LARGE_INTEGER Clock::ticks;
LARGE_INTEGER Clock::ticksPerSecond;

LARGE_INTEGER Clock::getHardwareCounterValue() {
	LARGE_INTEGER v;
	QueryPerformanceCounter(&v);
	return v;
}

void Clock::init() {
	QueryPerformanceFrequency(&ticksPerSecond);
	ticks = getHardwareCounterValue();
}

double Clock::ticksToSeconds(LARGE_INTEGER _ticks) {
	return (double)_ticks.QuadPart / (double)ticksPerSecond.QuadPart;
}

LARGE_INTEGER Clock::secondsToTicks(double _seconds) {
	LARGE_INTEGER result;
	result.QuadPart = (LONGLONG)(_seconds * (double)ticksPerSecond.QuadPart);
	return result;
}

LARGE_INTEGER Clock::getCurrentTicks() {
	return getHardwareCounterValue();
}

LARGE_INTEGER Clock::getResolution() {
	return ticksPerSecond;
}

double Clock::getCurrentTime() {
	return ticksToSeconds(getCurrentTicks());
}