#pragma once

#include "windows.h"
#include "..\global_defines.h"

// NOTE: Keep track of performance for timing frames etc.
// https://msdn.microsoft.com/en-us/library/windows/desktop/dn553408(v=vs.85).aspx


/**
*	Keeps track of performance, counts the clocks and translates it to milliseconds. Also calculates frames per seconds and time delta.
*	Also stores a wall clock, that counts from when the program started in milliseconds.
*/
class win32_perf_query
{
	private:
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, Frequency;	//!< Values stored by windows performance queries.
	real64 PassedFrames;			//!< Counts frames elapsed, gets reset everytime the fps counter is updated.
	real64 PassedTimeInSeconds;		//!< Passed time in seconds, gets reset everythimg the fps counter is updated.
	real64 PassedFrameTimeInMS;		//!< How long time time the frame took to finish in milliseconds.
	real16 FramePerMS;				//!< How many frames per milliseconds, will be set depending on what targeted frame rate is set by.
	real16 TargetFrameRate;			//!< How many frames that will be displayed every second.
	real64 TimeDelta;				//!< Time delta is set depending on the current frame each frame. It is a normalized value.
	real64 WallClock;				//!< How long time has passed in milliseconds since program started.
	real64 Frame;					//!< How many frames that has passed since program started.
	real64 FPS;						//!< Current frames per second.

	void CountFramesPerSecond();	//!< Updates the current frames per second value, depending on how many frames has passed.
	
	public:
	// NOTE: Use QueryStart() in beginning of program loop, and QueryEnd() after everthing is done on frame.
	// WaitFrame() is called after QueryEnd(), it will call Sleep() to not go over targeted frame rate.
	// Returns 1 if it hit the target frame rate, or 0 if the frame were too slow and no sleep were made.

	void QueryStart();				//!< Start the performance query. Put in start of program loop.
	void QueryEnd();				//!< Ends the performance query. Put in end of program loop.
	bool WaitFrame();				//!< @brief Check if current frame were too slow. Call this after QueryEnd() if the program should be sleeping when too fast. @return Returns 1 if the frame were too slow, and the function called Sleep(), otherwise return 0.
	
	// NOTE: This will adjust the sleep time every frame, the framerate is set to 30.0 by default.
	/**
	*   @brief  Set the frame rate in which the program should render in. Is set to 30.0 by default if not called.
	*
	*   @param  TargetFrameRate The frame rate that the renderer should be targetting, for example 60.0.
	*/
	void SetTargetFrameRate(real16 TargetFrameRate);

	real64 GetElapsedFrameTimeBeforeSleepMS() const;	//!< @brief Get the time it took to finish the frame. @return Time in milliseconds. 
	real64 GetCalculatedSleepTimeMS() const;			//!< @brief Get the time difference if the frame were faster than the targeted value. @return Time in milliseconds. 
	real64 GetTotalTimeMS();							//!< @brief Get the total time of the frame, including if WaitFrame() were called. @return Time in milliseconds. 
	real64 GetTimeDelta() const;						//!< @brief Get the time delta depending on current frame rate. @return Normalized value 0 < x < 1. 
	real64 GetWallClock() const;						//!< @brief Get time elapsed since program started running. @return Time in milliseconds. 
	real64 GetFrame() const;							//!< @brief Get elapsed frames since program started running. @return Number of frames passed. 
	real64 GetFPS() const;								//!< @brief Get the current frames per second measurement. @return Value of current fps. 

	public:
	win32_perf_query();									//!< Default constructor.
};
