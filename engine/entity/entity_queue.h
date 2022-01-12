#pragma once

#include "..\renderer\render_mkrenderable.h"
#include "..\renderer\render_queue.h"
#include "collision_detect.h"
#include "entity_object.h"
#include "..\debug\debug_datacollector.h"
#include <memory>
#include <vector>
#include <list>

/**
*	Entities that are active are stored in entity queue. All active entities will be updated every frame.
*/
class entity_queue
{
	private:
	static std::vector<std::shared_ptr<entity_object>> Entities;					//!< Entity queue, that will be iterated through every frame, and update the entities.
	static std::vector<std::shared_ptr<entity_object>> EntitiesCalledInEntities;	//!< When entities creates entities from within, these entities will be pushed to this queue.
	static bool CallingEntities;													//!< A check to see if entities are being iterated.
	collision_detect Collision;														//!< Entities that is collideable will be pushed to collision queue.

	public:
	void Create(entity_object *Entity);												//!< Creates a entity, pushes it to the entity queue. @param *Entity Pointer to an entity object.
	void CheckCollision();															//!< Execute the collision queue, checks all entities that has been pushed to this queue. Empties every frame.
	void Queue();																	//!< Check all entities and call Update() on all entities.

	public:
	entity_queue();
}; 

/**
*	Predicate to check if an entity is active and should be updated or not.
*/
struct is_inactive
{
	bool operator()(const std::shared_ptr<entity_object> &Entity)
	{
		return (!(Entity->GetIsActive()));
	}
};