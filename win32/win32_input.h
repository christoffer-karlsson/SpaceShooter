#pragma once

#include "..\global_defines.h"

#define MAX_KEYS		256
#define MAX_MOUSE_BTN	5

enum virtual_key_codes;
enum mouse_button;

struct mouse_info;

/**
*	Stores the current state of raw input from the message handler for keyboard and mouse.
*	The input arrays are static, so this class can be called in any scope, to get the raw input data.
*/
class win32_input
{
	private:
	static mouse_info Mouse[];		//!< Array with state of mouse buttons, and mouse position in window.
	static bool Key[];				//!< Array with state of keyboard buttons.

	public:

	/**
	*   @brief  Updates the state for given button on keyboard.
	*
	*   @param  Button			Value of the button.
	*   @param  ButtonState		Specifies if button is pressed or released.
	*
	*   @return void
	*/
	void UpdateKeyStates(int16 Button, bool ButtonState);

	/**
	*   @brief  Updates the state for given button on mouse.
	*
	*   @param  PositionX		The X coordinate in window when the button was pressed/released.
	*   @param  PositionY		The Y coordinate in window when the button was pressed/released.
	*   @param  Button			Which button was pressed/released.
	*   @param  ButtonState		Specifies if button is pressed or released.
	*
	*   @return void
	*/
	void UpdateMouseStates(int16 PositionX, int16 PositionY, mouse_button Button, bool ButtonState);

	/**
	*   @brief  Get current raw status for a keyboard button.
	*
	*   @param  Button			Which button to check.
	*
	*   @return If given button is currently held down, returns 1, otherwise 0.
	*/
	bool GetKeyState(virtual_key_codes Button) const;

	/**
	*   @brief  Get current raw status for a keyboard button.
	*
	*   @param  Button			Which button to check.
	*
	*   @return Returns a mouse_info struct, with the information about the specified button.
	*/
	mouse_info GetMouseState(mouse_button Button) const;
};

/**
*	Structure with raw mouse data.
*/
struct mouse_info
{
	bool ButtonState;		//!< Button state.
	int16 PositionX;		//!< X coordinate in window.
	int16 PositionY;		//!< Y coordinate in window.
};

/**
*	Virual key codes enumerated. Reference: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
*/
enum virtual_key_codes
{
	KEY_UP		= 0x26,
	KEY_DOWN	= 0x28,
	KEY_LEFT	= 0x25,
	KEY_RIGHT	= 0x27,
	KEY_0		= 0x30,
	KEY_1		= 0x31,
	KEY_2		= 0x32,
	KEY_3		= 0x33,
	KEY_4		= 0x34,
	KEY_5		= 0x35,
	KEY_6		= 0x36,
	KEY_7		= 0x37,
	KEY_8		= 0x38,
	KEY_9		= 0x39,
	KEY_W		= 0x57,
	KEY_A		= 0x41,
	KEY_S		= 0x53,
	KEY_D		= 0x44,
	KEY_O		= 0x4F,
	KEY_P		= 0x50,
	KEY_ESC		= 0x1B,
	KEY_SPACE	= 0x20
};

/**
*	Mouse button types enumerated.
*/
enum mouse_button
{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE
};