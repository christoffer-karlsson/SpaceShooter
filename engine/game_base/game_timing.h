#pragma once

#include "..\..\win32\win32_perf_query.h"

class game_timing
{
	private:
	static win32_perf_query *PerformanceQuery;

	public:
	// NOTE: Calculated time delta, depending how fast the game is running.
	real64 GetTimeDelta() const;

	// NOTE: Returns total time in ms since the program started.
	real64 GetWallClock() const;

	// NOTE: Returns total frames since program started.
	real64 GetFrame() const;

	// NOTE: Returns frame per second measurement.
	real64 GetFPS() const;

	public:
	game_timing();
	game_timing(win32_perf_query *PerformanceQuery);
};