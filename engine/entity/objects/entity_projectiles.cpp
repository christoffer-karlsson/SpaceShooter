#include "entity_projectiles.h"

entity_projectiles::entity_projectiles(entity_type Type, real32 PositionX, real32 PositionY, real32 PositionZ, real32 Rotation, real32 Velocity)
	: Velocity(Velocity), Rotation(Rotation), CurrentHitPoints(1.0), Animation(&AssetID)
{
	AssetID = "Source/data/projectiles/StandardLaser.bmp";
	this->Type = Type;

	IsActive = true;
	IsStatic = false;
	IsColliding = true;

	this->BaseHitPoints = 1.0;
	this->BaseDamage = 10.0;
	this->CollisionWidth = 16.0;
	this->CollisionHeight = 8.0;

	this->PositionX = PositionX;
	this->PositionY = PositionY;
	this->PositionZ = PositionZ;
	this->Scale = 1.0;
	this->Alpha = 1.0;
}

void entity_projectiles::Update()
{
	if (CurrentHitPoints <= 0)
	{
		IsActive = !Animation.SmallExplosion();
	}
	else
	{
		real64 dT = Timing.GetTimeDelta();
		if (PositionX < -0.5 || PositionX > 1.5 || PositionY < -0.5 || PositionY > 1.5)
		{
			IsActive = 0;
		}
		else
		{
			if (Rotation == 0.0) { PositionX += (dT * Velocity); }
			if (Rotation == 90.0) { PositionY += (dT * Velocity); }
			if (Rotation == 180.0) { PositionX -= (dT * Velocity); }
			if (Rotation == 270.0) { PositionY -= (dT * Velocity); }
		}
	}
}

void entity_projectiles::SetDamage(real32 Damage)
{
	CurrentHitPoints -= Damage;
}
