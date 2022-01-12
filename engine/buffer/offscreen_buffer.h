#pragma once

#include <iostream>
#include <windows.h>
#include "..\..\global_defines.h"
#include "..\..\win32\win32_base.h"

/**
*	The memory buffer for the pixels that is getting drawn to the window every frame.
*/
class offscreen_buffer
{
	private:
	static BITMAPINFO BitmapInfo;
	static HDC DisplayDeviceContext;
	static HWND WindowHandle;
	static uint32 *Memory;
	static int16 WindowWidth;
	static int16 WindowHeight;
	static int16 BufferWidth;
	static int16 BufferHeight;
	
	public:
	void DisplayBuffer() const;
	void InvalidateClientRect() const;

	public:
	int16 GetSize() const;
	int16 GetWidth() const;
	int16 GetHeight() const;
	uint32 *GetMemoryBegin() const;
	uint32 *GetMemoryEnd() const;

	public:
	offscreen_buffer();
	offscreen_buffer(win32_base *WindowState, int16 Width, int16 Height);
};