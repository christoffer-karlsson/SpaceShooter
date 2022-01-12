#include "game_timing.h"

win32_perf_query *game_timing::PerformanceQuery = nullptr;

real64 game_timing::GetTimeDelta() const
{
	return PerformanceQuery->GetTimeDelta();
}

real64 game_timing::GetWallClock() const
{
	return PerformanceQuery->GetWallClock();
}

real64 game_timing::GetFrame() const
{
	return PerformanceQuery->GetFrame();
}

real64 game_timing::GetFPS() const
{
	return PerformanceQuery->GetFPS();
}

game_timing::game_timing()
{
}

game_timing::game_timing(win32_perf_query *PerformanceQuery)
{
	this->PerformanceQuery = PerformanceQuery;
}
