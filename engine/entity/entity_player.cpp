#include "entity_player.h"

entity_player::entity_player(real32 PositionX, real32 PositionY, real32 PositionZ)
	: Velocity(0.0), LaserCooldown(0.0), Destroyed(false), CurrentHitPoints(100.0), Animation(&AssetID)
{
	AssetID = 0;
	this->Type = PLAYER;

	IsActive = true;
	IsStatic = false;
	IsColliding = true;

	this->BaseHitPoints = 100.0;
	this->BaseDamage = 10.0;
	this->MaxVelocity = 0.5;
	this->Acceleration = 0.1;

	this->CollisionWidth = 0;
	this->CollisionHeight = 0;

	this->PositionX = PositionX;
	this->PositionY = PositionY;
	this->PositionZ = PositionZ;
	this->Rotation = 0.0;
	this->Scale = 1.0;
	this->Alpha = 1.0;
}

void entity_player::Laser()
{
	if (!(LaserCooldown > 0.0))
	{
		entity_queue Entity;
		Entity.Create(new entity_projectiles(PLAYER_PROJECTILE, PositionX + 0.01, PositionY - 0.015, PositionZ - 1, 0.0, 1.0));
		Entity.Create(new entity_projectiles(PLAYER_PROJECTILE, PositionX + 0.01, PositionY + 0.015, PositionZ - 1, 0.0, 1.0));
		LaserCooldown = 0.1 * Timing.GetFPS();
	}
	else
	{
		LaserCooldown--;
	}
}

void entity_player::Update()
{
	bool MovementInput = 0;
	real64 dT = Timing.GetTimeDelta();

	// NOTE(temp): Basic input handling out here for testing purposes.
	if (Input.Key(KEY_W)) 
	{ 
		if (Velocity < MaxVelocity)
		{
			Velocity += dT * Acceleration;
		}
		else if (Velocity >= MaxVelocity)
		{
			Velocity = MaxVelocity;
		}
		MovementInput = 1;
		PositionY += dT * Velocity;

		Animation.MoveUp();
	}
	if (Input.Key(KEY_A))
	{ 
		if (Velocity < MaxVelocity)
		{
			Velocity += dT * Acceleration;
		}
		else if (Velocity >= MaxVelocity)
		{
			Velocity = MaxVelocity;
		}
		MovementInput = 1;
		PositionX -= dT * Velocity;

		Animation.MoveBackward();
	}
	if (Input.Key(KEY_S))
	{
		if (Velocity < MaxVelocity)
		{
			Velocity += dT * Acceleration;
		}
		else if (Velocity >= MaxVelocity)
		{
			Velocity = MaxVelocity;
		}
		MovementInput = 1;
		PositionY -= dT * Velocity;

		Animation.MoveDown();
	}
	if (Input.Key(KEY_D))
	{ 
		if (Velocity < MaxVelocity)
		{
			Velocity += dT * Acceleration;
		}
		else if (Velocity >= MaxVelocity)
		{
			Velocity = MaxVelocity;
		}
		MovementInput = 1;
		PositionX += dT * Velocity;

		Animation.MoveForward();
	}

	if (!MovementInput)
	{
		Animation.Idle();
	}

	if ((Velocity > 0.0) && !MovementInput)
	{
		Velocity -= dT * Acceleration * 0.5;
	}

	if (Input.Key(KEY_SPACE))
	{ 
		Laser(); 
	}

	if (CurrentHitPoints <= 0)
	{
		Destroyed = 1;
		//IsActive = 0;
		// Effect?
	}

	// Bound to screen.
	if (PositionX > 1.0) { PositionX = 1.0; }
	if (PositionX < 0.0) { PositionX = 0.0; }
	if (PositionY > 1.0) { PositionY = 1.0; }
	if (PositionY < 0.0) { PositionY = 0.0; }
}

void entity_player::SetDamage(real32 Damage)
{
	CurrentHitPoints -= Damage;
}
