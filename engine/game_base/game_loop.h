#pragma once

#include "..\input\game_input.h"
#include "..\entity\entity_header.h"
#include "..\game_base\game_timing.h"
#include "..\buffer\offscreen_buffer.h"
#include "..\tools\random_inline.h"

class game_loop
{
	private:
	offscreen_buffer Buffer;
	game_timing Timing;
	game_input Input;
	entity_queue Entity;
	render_base Render; //temp

	bool PlayerCreated;
	real32 CameraX;
	real64 TimeStamp;
	bool EntityTest;

	public:
	game_loop();
	void Main();
};