#include "animation_enemy_1.h"

animation_enemy_1::animation_enemy_1(const char8 **ID) : ID(ID), IdleFrame(0.0), DestroyedFrame(0.0), IdleTimeStamp(0.0), Timing() { }

void animation_enemy_1::Idle()
{
	real64 CurrentTime = Timing.GetWallClock();
	real64 dT = Timing.GetTimeDelta();
	if (CurrentTime > IdleTimeStamp)
	{
		if		(IdleFrame == 0.0) { *ID = "Source/data/enemy1/EnemyShip_1_Idle.bmp"; IdleFrame = 1.0; }
		else if (IdleFrame == 1.0) { *ID = "Source/data/enemy1/EnemyShip_1_Idle.bmp"; IdleFrame = 0.0; }
		IdleTimeStamp = CurrentTime + (dT * 10000.0);
	}
}

bool animation_enemy_1::Destroyed()
{
	bool AnimationDone = 0;
	real64 CurrentTime = Timing.GetWallClock();
	real64 dT = Timing.GetTimeDelta();
	if (CurrentTime > DestroyedTimeStamp)
	{
		if		(DestroyedFrame == 0.0) { *ID = "Source/data/enemy1/EnemyShip_1_Destroyed_1.bmp"; DestroyedFrame = 1.0; }
		else if (DestroyedFrame == 1.0) { *ID = "Source/data/enemy1/EnemyShip_1_Destroyed_2.bmp"; DestroyedFrame = 2.0; }
		else if (DestroyedFrame == 2.0) { *ID = "Source/data/enemy1/EnemyShip_1_Destroyed_3.bmp"; DestroyedFrame = 3.0; }
		else if (DestroyedFrame == 3.0) { *ID = "Source/data/enemy1/EnemyShip_1_Destroyed_4.bmp"; DestroyedFrame = 4.0; }
		else if (DestroyedFrame == 4.0) { *ID = "Source/data/enemy1/EnemyShip_1_Destroyed_5.bmp"; DestroyedFrame = 5.0; }
		else if (DestroyedFrame == 5.0) { *ID = "Source/data/enemy1/EnemyShip_1_Destroyed_6.bmp"; DestroyedFrame = 6.0; }
		else if (DestroyedFrame == 6.0) { *ID = "Source/data/enemy1/EnemyShip_1_Destroyed_7.bmp"; DestroyedFrame = 7.0; }
		else if (DestroyedFrame == 7.0) { *ID = "Source/data/enemy1/EnemyShip_1_Destroyed_8.bmp"; DestroyedFrame = 8.0; AnimationDone = 1; }
		DestroyedTimeStamp = CurrentTime + (dT * 10000.0);
	}
	return AnimationDone;
}