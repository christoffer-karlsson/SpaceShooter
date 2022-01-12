#pragma once

#include "..\..\global_defines.h"
#include <memory>

/**
*	Takes raw information about an object, and translate it to a renderable object, which can be
*	pushed to the render queue.
*/
class renderable_object
{
	private:
	const char8 *AssetID;
	real32 PositionX;
	real32 PositionY;
	real32 PositionZ;
	real32 Rotation;
	real32 Scale;
	real32 Alpha;

	public:
	const char8 *GetAssetID() const;
	real32 GetPositionX() const;
	real32 GetPositionY() const;
	real32 GetPositionZ() const;
	real32 GetRotation() const;
	real32 GetScale() const;
	real32 GetAlpha() const;

	public:
	renderable_object(const char8 *ID, real32 PositionX, real32 PositionY, real32 PositionZ, real32 Rotation, real32 Scale, real32 Alpha);
};

/**
*	Predicate to sort renderable objects according to the Z position.
*/
struct z_sort
{
	bool operator()(const std::unique_ptr<renderable_object> &L, const std::unique_ptr<renderable_object> &R)
	{
		return (L->GetPositionZ() < R->GetPositionZ());
	}
};