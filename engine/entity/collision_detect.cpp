#include "collision_detect.h"

std::vector<std::shared_ptr<entity_object>> collision_detect::EntityCollisionPositions;

void collision_detect::Push(std::shared_ptr<entity_object> Entity)
{
	EntityCollisionPositions.push_back(Entity);
}

void collision_detect::RectangleCheck()
{
	for (std::vector<std::shared_ptr<entity_object>>::iterator ItA = EntityCollisionPositions.begin(); 
		ItA != EntityCollisionPositions.end(); 
		ItA++)
	{
		for (std::vector<std::shared_ptr<entity_object>>::iterator ItB = EntityCollisionPositions.begin(); 
			ItB != EntityCollisionPositions.end(); ItB++)
		{
			// NOTE: Prevent object for checking collision with itself.
			if (ItA != ItB)
			{
				offscreen_buffer Buffer;
				entity_info A = ItA->get()->GetEntityData();
				entity_info B = ItB->get()->GetEntityData();
				real32 APositionX = A.PositionX * Buffer.GetWidth();
				real32 BPositionX = B.PositionX * Buffer.GetWidth();
				real32 APositionY = A.PositionY * Buffer.GetHeight();
				real32 BPositionY = B.PositionY * Buffer.GetHeight();
				real32 AWidth = A.CollisionWidth;
				real32 BWidth = B.CollisionWidth;
				real32 AHeight = A.CollisionHeight;
				real32 BHeight = B.CollisionHeight;
				if (!(APositionX + AWidth  < BPositionX ||
					  BPositionX + BWidth  < APositionX ||
					  APositionY + AHeight < BPositionY ||
					  BPositionY + BHeight < APositionY))
				{
					// NOTE: If collision was detected.
					collision_event(*ItA, *ItB);
				}
			}
		}
	}
	// NOTE: Clear the vector of all entitys.
	EntityCollisionPositions.clear();
}

collision_detect::collision_detect()
{
}
