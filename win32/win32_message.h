#pragma once

#include <windows.h>
#include "win32_base.h"
#include "win32_input.h"
#include "..\engine\buffer\offscreen_buffer.h"
#include <iostream>

/**
*	Handles the messages which is sent by windows message dispatcher.
*	Calls the appropriate function, depending of message. Works as a function overloader
*	since this is just a message handler/dispatcher, rather than a class that stores anything.
*	Returns 1 if the window message was handled by the program, if not returns 0.
*	If 0 is returned, make sure to handle the message with the default window message handler
*	instead.
*/
class win32_message
{
	private:
	win32_input *Input;		//!< Pointer to input class.

	protected:
	void WindowRedraw() const;															//!< Calls DisplayBuffer(), in the buffer if WM_PAINT message was recieved.
	void WindowDestroyed(win32_base *WindowState) const;								//!< Calls TerminateWindow(), in windows base if WM_DESTROY message was recieved.
	void WindowSizeChange(LPARAM LParam) const;											//!< Reports the new window size to the console debugger if WM_RESIZE message was recieved.
	void MouseButton(LPARAM LParam, mouse_button Button, bool ButtonState) const;		//!< Calls UpdateMouseState() if a WM_MOUSEBUTTONUP/WM_MOUSEBUTTONDOWN message was recieved.
	void KeyButton(WPARAM WParam, bool KeyState) const;									//!< Calls \ref UpdateKeyState() if a WM_KEYDOWN/WM_KEYUP message was recieved.

	public:

	/**
	*   @brief  Function overload, which handles the window messages.
	*
	*   @param  Message			Value of the message given by windows procedure.
	*   @param  WParam			WParam given by windows callback procedure.
	*   @param  LParam			LParam given by windows callback procedure.
	*   @param  *WindowsState	Pointer to win32_base.
	*   @param  *WindowInput	Pointer to win32_input.
	*
	*   @return Returns 1 if message was handled, otherwise 0.
	*/
	bool operator()(UINT Message, WPARAM WParam, LPARAM LParam, win32_base *WindowState, win32_input *WindowInput);
};