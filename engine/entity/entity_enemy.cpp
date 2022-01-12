#include "entity_enemy.h"

entity_enemy::entity_enemy(real32 PositionX, real32 PositionY, real32 PositionZ)
	: Velocity(0.0), CurrentHitPoints(250.0), LaserCooldown(0.0), ChangeMovementY(false), Animation(&AssetID)
{
	AssetID = 0;
	this->Type = ENEMY;

	IsActive = true;
	IsStatic = false;
	IsColliding = true;

	this->BaseHitPoints = 500.0;
	this->BaseDamage = 10.0;
	this->MaxVelocity = 0.5;
	this->Acceleration = 0.1;

	this->CollisionWidth = 64.0;
	this->CollisionHeight = 64.0;

	this->PositionX = PositionX;
	this->PositionY = PositionY;
	this->PositionZ = PositionZ;
	this->Rotation = 0.0;
	this->Scale = 1.0;
	this->Alpha = 1.0;
}

void entity_enemy::Laser()
{
	if (!(LaserCooldown > 0.0))
	{
		entity_queue Entity;
		Entity.Create(new entity_projectiles(ENEMY_PROJECTILE, PositionX - 0.01, PositionY, PositionZ - 1.0, 180.0, 1.0));
		LaserCooldown = 2.0 * Timing.GetFPS();
	}
	else
	{
		LaserCooldown--;
	}
}

void entity_enemy::Update()
{
	real64 dT = Timing.GetTimeDelta();

	// Bound to screen.
	if (PositionX > 1.0) { PositionX = 1.0; }
	if (PositionX < 0.0) { PositionX = 0.0; }
	if (PositionY > 1.0) { PositionY = 1.0; }
	if (PositionY < 0.0) { PositionY = 0.0; }

	if (CurrentHitPoints <= 0)
	{
		IsColliding = false;
		IsActive = !(Animation.Destroyed());
	}
	else
	{
		if (ChangeMovementY)
		{
			PositionY += dT * 0.1;
			if (PositionY > RandomDouble(0.5, 0.95)) { ChangeMovementY = !ChangeMovementY; }
		}

		if (!ChangeMovementY)
		{
			PositionY -= dT * 0.1;
			if (PositionY < RandomDouble(0.05, 0.50)) { ChangeMovementY = !ChangeMovementY; }
		}

		Animation.Idle();
	}

	Laser();
}

void entity_enemy::SetDamage(real32 Damage)
{
	CurrentHitPoints -= Damage;
}