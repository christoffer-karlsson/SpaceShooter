#include "entity_star.h"

uint32 entity_star::EntityCount = 0;

entity_star::entity_star(const char8 *ID, real32 PositionX, real32 PositionY, real32 PositionZ, real32 Direction, real32 Velocity)
	: Velocity(Velocity)
{
	AssetID = ID;
	this->Type = STAR;

	IsActive = true;
	IsStatic = false;
	IsColliding = false;

	this->PositionX = PositionX;
	this->PositionY = PositionY;
	this->PositionZ = PositionZ;
	this->Rotation = 0.0;
	this->Scale = 1.0;
	this->Alpha = 1.0;

	this->EntityCount++;
}

entity_star::~entity_star()
{
	EntityCount--;
}

uint32 entity_star::GetEntityCount()
{
	return entity_star::EntityCount;
}

void entity_star::Update()
{
	game_input Input;
	real64 dT = Timing.GetTimeDelta();
	if (PositionX < -0.5 || PositionX > 1.5 || PositionY < -0.5 || PositionY > 1.5)
	{
		IsActive = 0;
	}
	else
	{
		PositionX -= (dT * Velocity);
	}
	// NOTE: Adjust the stars abit in x-direction when these inputs are made.
	if (Input.Key(KEY_W))
	{
		PositionY -= (dT * 0.02);
	}
	if (Input.Key(KEY_S))
	{
		PositionY += (dT * 0.02);
	}
}