#include "game_input.h"

win32_input *game_input::WindowsInput = nullptr;
real64 game_input::MouseTimeStamp = 0;

game_input::game_input()
{
}

game_input::game_input(win32_input *WindowsInput)
{
	this->WindowsInput = WindowsInput;
}

bool game_input::Key(virtual_key_codes Button)
{
	return WindowsInput->GetKeyState(Button);
}

mouse_info game_input::Mouse(mouse_button Button)
{
	return WindowsInput->GetMouseState(Button);
}
