#pragma once

#include "..\engine\game_base\game_timing.h"
#include "..\engine\entity\entity_object.h"

class animation_player
{
	private:
	const char8 **ID;
	game_timing Timing;
	real64 TimeStamp;
	real64 IdleFrame;

	public:
	void Idle();
	void MoveUp();
	void MoveDown();
	void MoveForward();
	void MoveBackward();
	void Destroyed();

	public:
	animation_player(const char8 **ID);
};