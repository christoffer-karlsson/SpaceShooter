#include "win32_perf_query.h"

win32_perf_query::win32_perf_query()
	: StartingTime({}), EndingTime({}), ElapsedMicroseconds({}), Frequency({}), PassedFrames(0.0), PassedTimeInSeconds(0.0), PassedFrameTimeInMS(0.0),
	FPS(0.0), TargetFrameRate(30.0), FramePerMS(0.0), TimeDelta(0.0), WallClock(0.0), Frame(0.0)
{
	SetTargetFrameRate(30.0);
}

void win32_perf_query::QueryStart()
{
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);
}

void win32_perf_query::QueryEnd()
{
	QueryPerformanceCounter(&EndingTime);

	// Convert from elapsed number of ticks to microseconds.
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	// Convert microseconds to milliseconds.
	PassedFrameTimeInMS = ElapsedMicroseconds.QuadPart * 0.001;

	// Save some information for game timings.
	WallClock += GetTotalTimeMS();
	TimeDelta = 1 / FPS;
	Frame++;

	CountFramesPerSecond();
}

void win32_perf_query::SetTargetFrameRate(real16 TargetFrameRate)
{
	if (!(TargetFrameRate < 30.0))
	{
		this->TargetFrameRate = TargetFrameRate;
		FramePerMS = 1000.0 / TargetFrameRate;
	}
}

bool win32_perf_query::WaitFrame()
{
	bool Result = 0;
	if (GetCalculatedSleepTimeMS() > 0.0)
	{
		// Sleep for before next frame if the previous frame were too fast.
		Sleep(GetCalculatedSleepTimeMS());
		Result = 1;
	}
	return Result;
}

real64 win32_perf_query::GetElapsedFrameTimeBeforeSleepMS() const
{
	return PassedFrameTimeInMS;
}

real64 win32_perf_query::GetCalculatedSleepTimeMS() const
{
	real64 SleepTime = FramePerMS - PassedFrameTimeInMS;
	if (SleepTime < 0.0)
	{
		SleepTime = 0.0;
	}
	return (SleepTime);
}

real64 win32_perf_query::GetTotalTimeMS()
{
	return (PassedFrameTimeInMS + GetCalculatedSleepTimeMS());
}

void win32_perf_query::CountFramesPerSecond()
{
	if (PassedFrames > 10.0)
	{
		if (PassedTimeInSeconds > 0.0)
		{
			FPS = PassedFrames / PassedTimeInSeconds;
		}
		// Reset the counter, when the number of frames is reached.
		PassedFrames = 0.0;
		PassedTimeInSeconds = 0.0;
	}
	else
	{
		// Convert to seconds from ms, increment frame counter, add time.
		// Also, do a check if the frame timing was hit, if not, dont get ElapsedTime.
		PassedFrames++;
		PassedTimeInSeconds += (GetTotalTimeMS() * 0.001);
	}
}

real64 win32_perf_query::GetFPS() const
{
	return FPS;
}

real64 win32_perf_query::GetTimeDelta() const
{
	return TimeDelta;
}

real64 win32_perf_query::GetWallClock() const
{
	return WallClock;
}

real64 win32_perf_query::GetFrame() const
{
	return Frame;
}