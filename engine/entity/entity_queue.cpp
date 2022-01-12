#include "entity_queue.h"

std::vector<std::shared_ptr<entity_object>> entity_queue::Entities;
std::vector<std::shared_ptr<entity_object>> entity_queue::EntitiesCalledInEntities;
bool entity_queue::CallingEntities = false;

entity_queue::entity_queue() : Collision()
{ 
}

// NOTE: Push the entity into the queue. If the entity is created from within an entity, push
// it to a separate vector, since it can't be pushed to the same vector being read from.
// Also returns the entity ID if it is needed.
void entity_queue::Create(entity_object *Entity)
{
	if (!CallingEntities)
	{
		Entities.push_back(std::shared_ptr<entity_object>(Entity));
	}
	else
	{
		EntitiesCalledInEntities.push_back(std::shared_ptr<entity_object>(Entity));
	}
}

void entity_queue::CheckCollision()
{
	Collision.RectangleCheck();
}

void entity_queue::Queue()
{
	// NOTE: Using shared_ptr since I want this to get copied. The reason is that
	// entities should be able to create new entities while the vector of entities is
	// iterating. Therefor unable to push the same vector from which the entities are
	// called. Maybe there is a better solution?
	std::copy(EntitiesCalledInEntities.begin(), EntitiesCalledInEntities.end(), std::back_inserter(Entities));
	EntitiesCalledInEntities.clear();

	// NOTE: Temporary data collection.
	debug_datacollector(0, Entities.size());

	CallingEntities = true;
	for (std::vector<std::shared_ptr<entity_object>>::iterator It = Entities.begin(); 
		 It != Entities.end(); 
		 It++)
	{
		if (It->get()->GetIsActive())
		{
			It->get()->Update();
			It->get()->Render();

			// NOTE: If the entity is flagged as it can be collided, push it to the collide queue.
			if (It->get()->GetIsColliding())
			{
				Collision.Push(*It);
			}
		}
	}
	CallingEntities = false;

	// NOTE: Remove inactive entities.
	Entities.erase(std::remove_if(Entities.begin(), Entities.end(), is_inactive()), Entities.end());
}