#include "render_mkrenderable.h"

renderable_object::renderable_object(const char8 * ID, real32 PositionX, real32 PositionY, real32 PositionZ, real32 Rotation, real32 Scale, real32 Alpha) 
	: AssetID(ID), PositionX(PositionX), PositionY(PositionY), PositionZ(PositionZ), Rotation(Rotation), Scale(Scale), Alpha(Alpha)
{
}

const char8 *renderable_object::GetAssetID() const
{
	return AssetID;
}

real32 renderable_object::GetPositionX() const
{
	return PositionX;
}

real32 renderable_object::GetPositionY() const
{
	return PositionY;
}

real32 renderable_object::GetPositionZ() const
{
	return PositionZ;
}

real32 renderable_object::GetRotation() const
{
	return Rotation;
}

real32 renderable_object::GetScale() const
{
	return Scale;
}

real32 renderable_object::GetAlpha() const
{
	return Alpha;
}