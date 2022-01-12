#pragma once

#include "..\..\global_defines.h"
#include "..\input\game_input.h"
#include "..\game_base\game_timing.h"
#include "..\renderer\render_queue.h"
#include "..\renderer\render_mkrenderable.h"

enum entity_type { PLAYER, ENEMY, PLAYER_PROJECTILE, ENEMY_PROJECTILE, STAR };

struct entity_info
{
	const char8 *ID;
	int64 EntityID;
	real32 CollisionWidth, CollisionHeight;
	real32 PositionX, PositionY, PositionZ, Rotation, Scale, Alpha;
};

/**
*	A object that has a position in the world. It can collide or be static.
*/

class entity_object
{
	protected:
	game_input Input;						//!< Since game commands is not implemented yet, the entitys can check for raw input. \todo { Implement proper input commands. }
	game_timing Timing;						//!< Timing for physics.
	render_queue RenderQueue;				//!< Entities can be pushed to render queue, from the entity queue.

	protected:
	entity_type Type;						//!< Entity type describes what type of object it is. It can therefore be accounted for when checking collision etc.
	const char8 *AssetID;					//!< The current graphical asset the object has.
	static uint64 EntityID;					//!< Unique entity id.
	real32 PositionX;						//!< X coordinate, relative to buffer width. 
	real32 PositionY;						//!< Y coordinate, relative to buffer height.
	real32 PositionZ;						//!< Z coordinate, higher Z value will be prioritized in render queue.
	real32 Rotation;						//!< Rotation in degrees. NOT USED!
	real32 Scale;							//!< Scale the object, default 1.0. NOT USED!
	real32 Alpha;							//!< Alpha value of object. NOT USED!
	real32 CollisionWidth;					//!< The width of collision model.
	real32 CollisionHeight;					//!< The height of collision model.

	real32 BaseHitPoints;					//!< Hitpoint of the entity. This can be set to 0 if object is static. Otherwise it can be used to check if the object should be in the world still.
	real32 BaseDamage;						//!< The base damage of the entity. This will decide how much SetDamage() will do to another object.
	real32 MaxVelocity;						//!< The max velocity the entity can have.
	real32 Acceleration;					//!< The acceleration speed of the entity.

	bool IsActive;							//!< If entity is active, it will be updated in the entity queue.
	bool IsStatic;							//!< If entity is static, it will not interact with other entities in the world, or be able to move.
	bool IsColliding;						//!< If entity is colliding, it will get pushed to the collision detection queue.

	public:
	virtual void Update() = 0;				//!< Every derived entity class needs to have an update function.
	void Render();							//!< Pushes the entity to the render queue as a renderable object.

	// NOTE: Get.
	uint64 GetEntityID() const;				//!< Get entity unique id.
	entity_info GetEntityData();			//!< Get all the information needed in order to make the entity renderable. @return Returns a entity_info structure.
	entity_type GetType() { return Type; }	//!< Get the entity type. @return Return a entityp_type enumerated value.
	bool GetIsActive() const;				//!< Get the IsActive status. @return 1 = Active or 0 = inactive.
	bool GetIsStatic() const;				//!< Get the IsStatic status. @return 1 = Is static or 0 = is not static.
	bool GetIsColliding() const;			//!< Get the IsColliding status. @return 1 = Is colliding, or 0 = is not colliding.
	real32 GetBaseDamage() const;			//!< Get base damage of entity. @return Base damage of unit.

	// NOTE: Set.
	void SetActive();						//!< Set the entity as active.
	void SetDeactive();						//!< Deactivate object.
	void SetStatic();						//!< Set object as static.
	void SetNotStatic();					//!< Set object as not static.
	void SetIsColliding();					//!< Set object to be able to collide.
	void SetIsNotColliding();				//!< Set object to be unable to collide.

	void SetAssetID(const char8 *AssetID);	//!< Set the current asset that the entity is using. @param *AssetID Asset id.
	virtual void SetDamage(real32 Damage);	//!< Set damage to the object. @param Damage A real value.

	public:
	entity_object();
	virtual ~entity_object();
}; 