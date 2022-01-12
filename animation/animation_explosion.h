#pragma once

#include "..\engine\game_base\game_timing.h"
#include "..\engine\entity\entity_object.h"

class animation_explosion
{
	private:
	const char8 **ID;
	game_timing Timing;
	real64 ExplosionTimeStamp;
	real64 ExplosionFrame;

	public:
	bool SmallExplosion();

	public:
	animation_explosion(const char8 **ID);
};