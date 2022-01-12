#include "game_loop.h"

game_loop::game_loop() : PlayerCreated(0), TimeStamp(0), EntityTest(false) { }

void game_loop::Main()
{
	// NOTE(temp): Draw background. (Temp method)
	Render.FillScreen(0xFF0b0b0b);

	if (!PlayerCreated)
	{
		Entity.Create(new entity_player(0.05, 0.5, 50.0));
		PlayerCreated = 1;
	}

	// NOTE(temp): Test entitys with mouse input.
	if (Input.Mouse(MOUSE_LEFT).ButtonState)
	{
		real64 CurrentTime = Timing.GetWallClock();
		if (CurrentTime > TimeStamp)
		{
			real32 MouseX = (real32)Input.Mouse(MOUSE_LEFT).PositionX / Buffer.GetWidth();
			real32 MouseY = (real32)Input.Mouse(MOUSE_LEFT).PositionY / Buffer.GetHeight();

			Entity.Create(new entity_enemy(MouseX, MouseY, 30.0));
			TimeStamp = CurrentTime + 200.0;

			debug_display("Entity created.");
		}
	}

#if 0
	// NOTE(test): Test entity performance.
	// Latest test 2018-01-02: 500 enemy ships at stable 60 fps, 1000 enemy ships at around 20-30 fps.
	if (!EntityTest)
	{
		for (int i = 0; i < 500; i++)
		{
			Entity.Create(new entity_enemy(RandomDouble(0.5, 1), RandomDouble(0.1, 0.9), 30.0));
		}
		EntityTest = true;
	}
#endif

	// NOTE: Space background.
	while (entity_star::GetEntityCount() < 20)
	{
		int16 RandomCommonStar = rand() % 4;
		if (RandomCommonStar == 0) { Entity.Create(new entity_star("Source/data/stars/small_star_8x8_1.bmp", 1.1, RandomDouble(0.0, 1.0), 100.0, 90.0, RandomDouble(0.8, 1.2))); }
		if (RandomCommonStar == 1) { Entity.Create(new entity_star("Source/data/stars/small_star_8x8_2.bmp", 1.1, RandomDouble(0.0, 1.0), 40.0, 90.0, RandomDouble(0.4, 1.0))); }
		if (RandomCommonStar == 2) { Entity.Create(new entity_star("Source/data/stars/small_star_8x8_3.bmp", 1.1, RandomDouble(0.0, 1.0), 40.0, 90.0, RandomDouble(0.1, 0.5))); }
	}
}