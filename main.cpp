/*	Project..:	Poor Man's Game Render Engine
	Author...:	Christoffer Karlsson Tanda
	Created..:	2017-12-20
	Last upd.:	????-??-??
	Depend1..:	<iostream>, <windows.h>
	Depend2..:	global_defines.h, win32_platform_header.h, engine_header.h
	Descrip..:	Main file for the engine.
*/

// NOTE: General info. Pixel structure is 0x A8 R8 G8 B8. And pixel buffer is
// index 0 standard.

// Define the size of the window. 
#define WINDOW_WIDTH  1600
#define WINDOW_HEIGHT 900

// Define the size of the buffer (it will be stretched to match window size).
#define OFFSCREEN_BUFFER_WIDTH	1600
#define OFFSCREEN_BUFFER_HEIGHT 900

// Define target upper frame rate target.
#define TARGET_FRAMERATE 60.0
float TargetFrameRate = TARGET_FRAMERATE;

#include <iostream>
#include <windows.h>

#include "global_defines.h"
#include "win32\win32_platform_header.h"
#include "engine\engine_header.h"
#include "engine\game_base\game_loop.h"
#include "engine\game_base\game_timing.h"

// Initiate base classes. These has to be declared before the window callback
// declaration. Because of this they all have a initialization method.
// These are getting constructed and initialized before the main loop begins, so
// the constructors does not have to be super efficient.
win32_base *const WindowBase = new win32_base;
win32_input *const WindowInput = new win32_input;

// Window procedure callback, for checking and handling windows messages.
// Dependent on WindowState, WindowInput and Render.
LRESULT CALLBACK WindowProcedure( HWND Window, UINT Message, WPARAM WParam, LPARAM LParam );

int main()
{
	bool Booted = 0;
	bool ShowDebug = 1;
	real64 TimeStamp = 0;
	std::cout << "DEBUG: Console started.\n";

	WindowBase->Initialize( WindowProcedure, WINDOW_WIDTH, WINDOW_HEIGHT );

	WindowBase->ConstructWindow();

	// NOTE: Initiate performance counter.
	win32_perf_query PerformanceQuery;
	// NOTE: Initiate debug messenger.
	debug_display Debug;
	// NOTE: Load data here.
	asset_loader Asset;
	Asset.MainLoader();
	Asset.FontLoader();
	// NOTE: Initialize pixel buffer.
	offscreen_buffer Buffer( WindowBase, OFFSCREEN_BUFFER_WIDTH, OFFSCREEN_BUFFER_HEIGHT );
	// NOTE: Initialize the game input.
	game_input Input( WindowInput );
	// NOTE: Initialize game timings.
	game_timing Timing( &PerformanceQuery );
	// NOTE: Initialize game simulation.
	game_loop GameLoop;
	// NOTE: Initialize entity queue.
	entity_queue Entity;
	// NOTE: Initialize render queue.
	render_queue RenderQueue;

	debug_display( "Console started." );

	if( WindowBase->GetWindowHandle() )
	{
		MSG Message;
		while( WindowBase->GetIsRunning() )
		{
			// NOTE(info): Specify that the entire screen should be redrawn.
			Buffer.InvalidateClientRect();

			// NOTE(info): Get and dispatch messages. If there is no messages, returns 0.
			while( PeekMessage( &Message, 0, 0, 0, PM_REMOVE ) )
			{
				TranslateMessage( &Message );
				DispatchMessage( &Message );
			}

			// NOTE(info): Begin performance counter.
			PerformanceQuery.SetTargetFrameRate( TargetFrameRate );
			PerformanceQuery.QueryStart();

			// NOTE(temp): Delay the game loop for some time.
			if( !Booted && ( PerformanceQuery.GetWallClock() > 100 ) )
			{
				Booted = 1;
			}

			// NOTE(temp): Temporary debug key bindings!
			if( Input.Key( KEY_RIGHT ) )
			{
				TargetFrameRate = 60.0;
			}
			else if( Input.Key( KEY_LEFT ) )
			{
				TargetFrameRate = 30.0;
			}
			else if( Input.Key( KEY_DOWN ) )
			{
				real64 CurrentTime = Timing.GetWallClock();
				if( CurrentTime > TimeStamp )
				{

					ShowDebug = !ShowDebug;
				}
				TimeStamp = CurrentTime + 200.0;
			}

			// NOTE(info): Game logic, physics, create / update entities, etc.
			if( Booted )
			{
				GameLoop.Main();
				Entity.CheckCollision();
			}

			// NOTE(info): Update entities based on the game logic, and push them to render queue.
			Entity.Queue();

			// NOTE(info): Start the render queue for all objects.
			RenderQueue.ExecuteQueue();

			// NOTE: Update debug messenger.
			if( ShowDebug )
			{
				Debug.ShowTimedMessages();
				Debug.ShowTempDebug( &PerformanceQuery ); // temp
			}

			// NOTE(info): End frame timer and wait for the frame if it was
			// over the frame target, or the other way around.
			PerformanceQuery.QueryEnd();
			PerformanceQuery.WaitFrame();
		}
	}

	std::cout << "DEBUG: Window was terminated.\n";

	while( 1 )
	{
		// Keep console open for debug purposes after Windows is closed.	
		Sleep( 5000 );
	}
}

// Check to see if we can handle the message from the dispatcher, else if the function object
// returns 0, let Windows default handler take the message.
LRESULT CALLBACK WindowProcedure( HWND Window, UINT Message, WPARAM WParam, LPARAM LParam )
{
	LRESULT Result = 0;
	if( !( win32_message()( Message, WParam, LParam, WindowBase, WindowInput ) ) )
	{
		return DefWindowProc( Window, Message, WParam, LParam );
	}
	return Result;
}