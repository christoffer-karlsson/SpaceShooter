#pragma once

#include "..\..\animation\animation_player.h"
#include "entity_object.h"
#include "objects\entity_projectiles.h"
#include "entity_queue.h"

class entity_player : public entity_object
{
	private:
	animation_player Animation;
	real32 Velocity;
	real32 LaserCooldown;
	real32 CurrentHitPoints;
	bool Destroyed;

	protected:
	void Laser();

	public:
	void Update();
	void SetDamage(real32 Damage) override;

	public:
	entity_player(real32 PositionX, real32 PositionY, real32 PositionZ);
};

