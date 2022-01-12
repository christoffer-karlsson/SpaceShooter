#include "animation_explosion.h"

animation_explosion::animation_explosion(const char8 **ID) : ID(ID), ExplosionFrame(0.0), ExplosionTimeStamp(0.0), Timing() { }

bool animation_explosion::SmallExplosion()
{
	bool AnimationDone = 0;
	real64 CurrentTime = Timing.GetWallClock();
	real64 dT = Timing.GetTimeDelta();
	if (CurrentTime > ExplosionTimeStamp)
	{
			 if (ExplosionFrame == 0.0) { *ID = "Source/data/effects/SmallExplosion_0.bmp"; ExplosionFrame = 1.0; }
		else if (ExplosionFrame == 1.0) { *ID = "Source/data/effects/SmallExplosion_1.bmp"; ExplosionFrame = 2.0; }
		else if (ExplosionFrame == 2.0) { *ID = "Source/data/effects/SmallExplosion_2.bmp"; ExplosionFrame = 3.0; }
		else if (ExplosionFrame == 3.0) { *ID = "Source/data/effects/SmallExplosion_2.bmp"; ExplosionFrame = 0.0; AnimationDone = 1; }
		ExplosionTimeStamp = CurrentTime + (dT * 10000.0);
	}
	return AnimationDone;
}