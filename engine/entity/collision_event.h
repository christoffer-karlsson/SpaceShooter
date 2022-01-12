#pragma once

#include "entity_object.h"

// NOTE: This class explains what will happen once a collision is detected.
// Define the possible collision events in this class.

class collision_event
{
	private:
	std::shared_ptr<entity_object> EntityA;
	std::shared_ptr<entity_object> EntityB;

	void CheckCollisionType();

	public:
	collision_event(std::shared_ptr<entity_object> EntityA, std::shared_ptr<entity_object> EntityB);
};