#pragma once

#include "..\..\win32\win32_input.h"
#include "..\game_base\game_timing.h"

class game_input
{
	private:
	static win32_input *WindowsInput;
	static real64 MouseTimeStamp;

	public:
	bool Key(virtual_key_codes Key);
	mouse_info Mouse(mouse_button Button);

	public:
	game_input();
	game_input(win32_input *WindowsInput);
};