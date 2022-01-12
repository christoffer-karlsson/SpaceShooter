#include "win32_input.h"

bool win32_input::Key[MAX_KEYS] = {};
mouse_info win32_input::Mouse[MAX_MOUSE_BTN] = {};

void win32_input::UpdateKeyStates(int16 Button, bool ButtonState)
{
	Key[Button] = ButtonState;
}

void win32_input::UpdateMouseStates(int16 PositionX, int16 PositionY, mouse_button Button, bool ButtonState)
{
	Mouse[Button].ButtonState = ButtonState;
	Mouse[Button].PositionX = PositionX;
	Mouse[Button].PositionY = PositionY;
}

bool win32_input::GetKeyState(virtual_key_codes Button) const
{
	return Key[Button];
}

mouse_info win32_input::GetMouseState(mouse_button Button) const
{
	return Mouse[Button];
}
