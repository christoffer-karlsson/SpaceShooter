#pragma once

#include "..\global_defines.h"
#include <windows.h>

/**
*	Initialize and construct the window. Stores the handle pointer to the window
*	and windows class. Also stores buffer size, and client size.
*	Needs a handle to the window callback procedure. Call Initialize() after the
*	handle to the window callback is made, then call ConstructWindow() after a
*	window class is registered.
*/
class win32_base
{
	private:

	WNDCLASSEX WindowClass;			//!< Window class.
	HWND WindowHandle;				//!< Handle (pointer) to window.

	int16 Height;					//!< Buffer height.
	int16 Width;					//!< Buffer width.
	int16 ClientRectWidth;			//!< Window client width.
	int16 ClientRectHeight;			//!< Window client height.

	const char *ApplicationName;	//!< Name of application, which is shown in the window header.
	bool IsRunning;					//!< Running state of program.

	public:

	/**
	*   @brief  Stores the window class and sets the window size. This needs to be called after the window callback is initiated.
	*
	*   @param  WindowProcedure LRESULT of window callback.
	*   @param  Width			Window width.
	*   @param  Height			Window height.
	*   @return void
	*/
	void Initialize( WNDPROC WindowsProcedure, int16 Width, int16 Height );

	void ConstructWindow();					//!< @brief Constructs the window and stores the handle to it, call after class registration. @return void

	LPCSTR GetWindowClassName() const;		//!< @brief Get window class name. @return Window class name. 
	HWND GetWindowHandle() const;			//!< @brief Get handle to the window. @return Handle pointer to window. 
	bool GetIsRunning() const;				//!< @brief Get running state of the program. @return 1 = program is running, 0 = program is terminated. 
	int16 GetWidth() const;					//!< @brief Get width of the buffer. @return Buffer width. 
	int16 GetHeight() const;				//!< @brief Get height of the buffer. @return Buffer height. 
	int16 GetClientRectWidth() const;		//!< @brief Get width of the window. @return Window client width. 
	int16 GetClientRectHeight() const;		//!< @brief Get height of the window. @return Window client height. 

	void TerminateWindow();					//!< @brief Sets IsRunning to 0, which terminates the program. @return void

	win32_base();							//!< @brief Default constructor.
};