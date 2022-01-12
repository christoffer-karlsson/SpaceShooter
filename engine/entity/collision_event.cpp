#include "collision_event.h"

collision_event::collision_event(std::shared_ptr<entity_object> EntityA, std::shared_ptr<entity_object> EntityB) : EntityA(EntityA), EntityB(EntityB)
{
	CheckCollisionType();
}

void collision_event::CheckCollisionType()
{
	if (EntityA->GetType() == ENEMY && EntityB->GetType() == PLAYER_PROJECTILE || EntityB->GetType() == ENEMY && EntityA->GetType() == PLAYER_PROJECTILE)
	{
		EntityA->SetDamage(EntityB->GetBaseDamage());
		EntityB->SetDamage(EntityA->GetBaseDamage());
	}
}