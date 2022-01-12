#pragma once

#include "..\engine\game_base\game_timing.h"
#include "..\engine\entity\entity_object.h"

/**
*	Animation for entity type 'enemy_1'. Has pointer to the Asset ID for the entity, and are therefore able to
*	change it. Keeps track of time passed in milliseconds, to progress the animation and update the Asset ID for the entity.
*	This animation is specific to an entity-type for now. But it will be generalized in the future.
*/
class animation_enemy_1
{
	private:

	const char8 **ID;							//!< Pointer to the asset ID for the entity. 
	game_timing Timing;							//!< Timing object, to get wall clock and time delta.
	real64 IdleFrame;							//!< Tracks on which idle animation frame the entity is on.
	real64 IdleTimeStamp;						//!< Time stamps when the idle animation was updated, to delay next frame.
	real64 DestroyedFrame;						//!< Tracks on which destroyed animation frame the entity is on.
	real64 DestroyedTimeStamp;					//!< Time stamps when the destroyed animation was updated, to delay next frame.

	public:

	/**
	*   @brief  Call the idle animation update, typically when the object is not doing anything.
	*   @return void
	*/
	void Idle();

	/**
	*   @brief  Call the destroy animation for entity.
	*   @return Returns 1 if animation is done, otherwise 0.
	*/
	bool Destroyed();

	/**
	*   @brief  Default constructor for object.
	*   @param  ID Pointer to entity assed id.
	*/
	animation_enemy_1(const char8 **ID);
};