#pragma once
#include <Windows.h>

class Clock {
private:
	static LARGE_INTEGER ticks;
	static LARGE_INTEGER ticksPerSecond;

	Clock() {} // Singleton private constructor

	static LARGE_INTEGER getHardwareCounterValue(); // Get ticks from windows
public:
	static void init(); // Initialize the clock

	static double ticksToSeconds(LARGE_INTEGER _ticks); // Convert ticks to seconds
	static LARGE_INTEGER secondsToTicks(double _seconds); // Convert seconds to ticks

	static LARGE_INTEGER getCurrentTicks(); // Calls getHardwareCounterValue to get total ticks
	static LARGE_INTEGER getResolution(); // Get the speed of the clock
	static double getCurrentTime(); // Get the total ticks converted to seconds
};