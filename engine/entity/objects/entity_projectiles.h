#pragma once

#include "..\..\..\animation\animation_explosion.h"
#include "..\entity_object.h"

class entity_projectiles : public entity_object
{
	private:
	animation_explosion Animation;
	real32 Velocity;
	real32 Rotation;
	real32 CurrentHitPoints;

	public:
	void Update();
	void SetDamage(real32 Damage) override;

	public:
	entity_projectiles(entity_type Type, real32 PositionX, real32 PositionY, real32 PositionZ, real32 Rotation, real32 Velocity);
};

