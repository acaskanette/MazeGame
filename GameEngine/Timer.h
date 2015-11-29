#pragma once
#include "Clock.h"

class Timer {
private:
	LARGE_INTEGER ticks;
	double multiplier;
	bool paused;
public:
	Timer();

	void setPaused(bool _paused); // Change the timer's pause state
	bool isPaused(); // Whether the timer is paused
	void pause(); // Toggle pause state

	void setScale(double _scale); // Change the timer's multiplier scale
	double getScale(); // Get the timer's multiplier

	void updateTicks(LARGE_INTEGER _ticks); // Add ticks to the timer
	void updateSeconds(double _secs); // Add seconds to the timer
	void set(LARGE_INTEGER _ticks); // Set the timer's tick value
	void reset(); // Reset the timer's ticks to 0

	LARGE_INTEGER getTicks(); // Get the total ticks of the timer
	double getSeconds(); // Get the total seconds of the timer
	double getMillis(); // Get the total millis of the timer

	double calcDeltaSeconds(Timer& _other); // The difference between two timer's times
};