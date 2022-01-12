#include "offscreen_buffer.h"

uint32 *offscreen_buffer::Memory = nullptr;
BITMAPINFO offscreen_buffer::BitmapInfo = {};
HDC offscreen_buffer::DisplayDeviceContext = 0;
HWND offscreen_buffer::WindowHandle = 0;
int16 offscreen_buffer::WindowWidth = 0;
int16 offscreen_buffer::WindowHeight = 0;
int16 offscreen_buffer::BufferWidth = 0;
int16 offscreen_buffer::BufferHeight = 0;

offscreen_buffer::offscreen_buffer()
{
}

offscreen_buffer::offscreen_buffer(win32_base *WindowState, int16 Width, int16 Height)
{
	BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BitmapInfo.bmiHeader.biWidth = Width;
	BitmapInfo.bmiHeader.biHeight = Height;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biCompression = BI_RGB;

	WindowHandle = WindowState->GetWindowHandle();
	WindowWidth = WindowState->GetWidth();
	WindowHeight = WindowState->GetHeight();
	BufferWidth = Width;
	BufferHeight = Height;
	DisplayDeviceContext = GetDC(WindowState->GetWindowHandle());

	Memory = new uint32[WindowState->GetWidth() * WindowState->GetHeight()];

	std::cout << "DEBUG: Offscreen buffer initialization done!\n";
}

void offscreen_buffer::DisplayBuffer() const
{
	PAINTSTRUCT Paint;
	BeginPaint(WindowHandle, &Paint);
	StretchDIBits(DisplayDeviceContext, 0, 0, WindowWidth, WindowHeight, 0, 0, BufferWidth, BufferHeight, Memory, &BitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	EndPaint(WindowHandle, &Paint);
}

void offscreen_buffer::InvalidateClientRect() const
{
	// NOTE(fix): Specify that the entire window rectangle should be redrawn and deleted
	// when next paint is called. Maybe implement something that could use argument 2, so
	// the entire screen does not need to be redrawn?
	InvalidateRect(WindowHandle, 0, TRUE); 
}

int16 offscreen_buffer::GetSize() const
{
	return BufferWidth * BufferHeight;
}

int16 offscreen_buffer::GetWidth() const
{
	return BufferWidth;
}

int16 offscreen_buffer::GetHeight() const
{
	return BufferHeight;
}

uint32 *offscreen_buffer::GetMemoryBegin() const
{
	return Memory;
}

uint32 *offscreen_buffer::GetMemoryEnd() const
{
	return Memory + (BufferWidth * BufferHeight);
}