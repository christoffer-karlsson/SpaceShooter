#include "win32_message.h"

void win32_message::WindowRedraw() const
{
	offscreen_buffer Buffer;
	Buffer.DisplayBuffer();
}

void win32_message::WindowDestroyed(win32_base *WindowState) const
{
	WindowState->TerminateWindow();
	std::cout << "DEBUG: [MSG, WM_DESTROYED] Shutting down.\n"; 
}

void win32_message::WindowSizeChange(LPARAM LParam) const
{
	std::cout << "DEBUG: [MSG, WM_SIZE] (" << LOWORD(LParam) << "," << HIWORD(LParam) << ")\n";
}

void win32_message::MouseButton(LPARAM LParam, mouse_button Button, bool ButtonState) const
{
	offscreen_buffer Buffer;
	// NOTE: Flipping the Y-axis on HIWORD since it is reversed.
	Input->UpdateMouseStates(LOWORD(LParam), Buffer.GetHeight() - HIWORD(LParam), Button, ButtonState);
	//std::cout << "DEBUG: [MSG WM] (" << LOWORD(LParam) << "," << Buffer.GetHeight() - HIWORD(LParam) << ")\n";
}

void win32_message::KeyButton(WPARAM WParam, bool KeyState) const
{
	Input->UpdateKeyStates(WParam, KeyState);
	//std::cout << "DEBUG: [MSG, WM_KEYDOWN] " << (char8)WParam << "\n";
}

bool win32_message::operator()(UINT Message, WPARAM WParam, LPARAM LParam, win32_base *WindowState, win32_input *WindowInput)
{
	Input = WindowInput;

	// NOTE: If we did not handle a message, the result will be 0, and the default
	// windows handler will be called instead.
	bool Result = 0;

	if (Message == WM_SIZE)
	{
		WindowSizeChange(LParam);
		Result = 1;
	}
	else if (Message == WM_DESTROY)
	{
		WindowDestroyed(WindowState);
		Result = 1;
	}
	else if (Message == WM_PAINT)
	{
		WindowRedraw();
		Result = 1;
	}
	else if (Message == WM_LBUTTONDOWN)
	{
		MouseButton(LParam, MOUSE_LEFT, 1);
		Result = 1;
	}
	else if (Message == WM_RBUTTONDOWN)
	{
		MouseButton(LParam, MOUSE_RIGHT, 1);
		Result = 1;
	}
	else if (Message == WM_MBUTTONDOWN)
	{
		MouseButton(LParam, MOUSE_MIDDLE, 1);
		Result = 1;
	}
	else if (Message == WM_LBUTTONUP)
	{
		MouseButton(LParam, MOUSE_LEFT, 0);
		Result = 1;
	}
	else if (Message == WM_RBUTTONUP)
	{
		MouseButton(LParam, MOUSE_RIGHT, 0);
		Result = 1;
	}
	else if (Message == WM_MBUTTONUP)
	{
		MouseButton(LParam, MOUSE_MIDDLE, 0);
		Result = 1;
	}
	else if (Message == WM_KEYDOWN)
	{
		KeyButton(WParam, 1);
		Result = 1;
	}
	else if (Message == WM_KEYUP)
	{
		KeyButton(WParam, 0);
		Result = 1;
	}
	
	return Result;
}