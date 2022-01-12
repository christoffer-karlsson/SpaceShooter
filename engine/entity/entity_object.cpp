#include "entity_object.h"

uint64 entity_object::EntityID = 0;

entity_object::entity_object() : AssetID(0), IsActive(0)
{
	EntityID++;
}

entity_object::~entity_object()
{
}

void entity_object::Render()
{
	RenderQueue.PushToQueue(new renderable_object(AssetID, PositionX, PositionY, PositionZ, Rotation, Scale, Alpha));
}

entity_info entity_object::GetEntityData()
{
	entity_info Result = {};
	Result.ID = AssetID;
	Result.EntityID = EntityID;
	Result.PositionX = PositionX;
	Result.PositionY = PositionY;
	Result.PositionZ = PositionZ;
	Result.CollisionWidth = CollisionWidth;
	Result.CollisionHeight = CollisionHeight;
	Result.Rotation = Rotation;
	Result.Scale = Scale;
	Result.Alpha = Rotation;
	return Result;
}

bool entity_object::GetIsActive() const
{
	return IsActive;
}

bool entity_object::GetIsStatic() const
{
	return IsStatic;
}

bool entity_object::GetIsColliding() const
{
	return IsColliding;
}

void entity_object::SetAssetID(const char8 *AssetID)
{
	this->AssetID = AssetID;
}

void entity_object::SetDamage(real32 Damage)
{
}

real32 entity_object::GetBaseDamage() const
{
	return BaseDamage;
}

uint64 entity_object::GetEntityID() const
{
	return entity_object::EntityID;
}

void entity_object::SetActive()
{
	this->IsActive = 1;
}

void entity_object::SetDeactive()
{
	this->IsActive = 0;
}

void entity_object::SetStatic()
{
	IsStatic = 1;
}

void entity_object::SetNotStatic()
{
	IsStatic = 0;
}

void entity_object::SetIsColliding()
{
	IsColliding = 1;
}

void entity_object::SetIsNotColliding()
{
	IsColliding = 0;
}