#include "animation_player.h"

animation_player::animation_player(const char8 **ID) : ID(ID), IdleFrame(0.0), TimeStamp(0.0), Timing() { }

void animation_player::Idle()
{
	*ID = "Source/data/player/SpaceShip_Idle.bmp";
}

void animation_player::MoveUp()
{
	*ID = "Source/data/player/SpaceShip_Up.bmp";
}

void animation_player::MoveDown()
{
	*ID = "Source/data/player/SpaceShip_Down.bmp";
}

void animation_player::MoveForward()
{
	*ID = "Source/data/player/SpaceShip_Forward.bmp";
}

void animation_player::MoveBackward()
{
	*ID = "Source/data/player/SpaceShip_Back.bmp";
}

void animation_player::Destroyed()
{

}