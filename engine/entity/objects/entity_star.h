#pragma once

#include "..\entity_object.h"

class entity_star : public entity_object
{
	private:
	static uint32 EntityCount;
	real32 Velocity;

	public:
	static uint32 GetEntityCount();
	void Update();
	
	public:
	entity_star(const char8 *ID, real32 PositionX, real32 PositionY, real32 PositionZ, real32 Direction, real32 Velocity);
	~entity_star();
};