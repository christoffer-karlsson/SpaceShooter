#pragma once

#include "entity_object.h"
#include "objects\entity_projectiles.h"
#include "entity_queue.h"
#include "..\..\animation\animation_enemy_1.h"
#include "..\tools\random_inline.h"

class entity_enemy : public entity_object
{
	private:
	animation_enemy_1 Animation;
	real32 Velocity;
	real32 CurrentHitPoints;
	real32 LaserCooldown;
	bool ChangeMovementY;

	protected:
	void Laser();

	public:
	void Update();
	void SetDamage(real32 Damage) override;

	public:
	entity_enemy(real32 PositionX, real32 PositionY, real32 PositionZ);
};