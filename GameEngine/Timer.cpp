#include "Timer.h"

Timer::Timer() : multiplier(1.0), paused(false) {
	ticks.QuadPart = 0L;
}

void Timer::setPaused(bool _paused) {
	paused = _paused;
}

bool Timer::isPaused() {
	return paused;
}

void Timer::pause() {
	paused = !paused ? true : false;
}

void Timer::setScale(double _scale) {
	multiplier = _scale;
}

double Timer::getScale() {
	return multiplier;
}

void Timer::updateTicks(LARGE_INTEGER _ticks) {
	if (!paused)
		ticks.QuadPart += _ticks.QuadPart * multiplier;
}

void Timer::updateSeconds(double _secs) {
	updateTicks(Clock::secondsToTicks(_secs));
}

void Timer::set(LARGE_INTEGER _ticks) {
	if (!paused)
		ticks = _ticks;
}

void Timer::reset() {
	ticks.QuadPart = 0L;
}

LARGE_INTEGER Timer::getTicks() {
	return ticks;
}

double Timer::getSeconds() {
	return Clock::ticksToSeconds(ticks);
}

double Timer::getMillis() {
	return getSeconds() * 1000;
}

double Timer::calcDeltaSeconds(Timer& _other) {
	LARGE_INTEGER delta;
	delta.QuadPart = ticks.QuadPart - _other.ticks.QuadPart;
	return Clock::ticksToSeconds(delta);
}