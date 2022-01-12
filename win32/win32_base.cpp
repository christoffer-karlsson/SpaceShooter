#include "win32_base.h"

win32_base::win32_base()
	: ApplicationName( "Poor Man's Game Engine | 0.01 | by Christoffer Karlsson Tanda" ), IsRunning( 1 )
{
	// Create the class to use for the window.
	WindowClass = {};									/* Contains window class information. It is used with the RegisterClassEx and GetClassInfoEx functions.*/
	WindowClass.cbSize = sizeof( WNDCLASSEX );			/* The size, in bytes, of this structure. Set this member to sizeof(WNDCLASSEX). */
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;		/* The class style(s).This member can be any combination of the Class Styles: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx */
	WindowClass.lpfnWndProc = 0;						/* A pointer to the window procedure. */
	WindowClass.hInstance = GetModuleHandle( 0 );			/* A handle to the instance that contains the window procedure for the class. */
	WindowClass.hIcon = LoadIcon( 0, IDI_APPLICATION );	/* A handle to the class icon. This member must be a handle to an icon resource. If this member is NULL, the system provides a default icon. */
	WindowClass.hCursor = LoadCursor( 0, IDC_ARROW );		/* A handle to the class cursor. This member must be a handle to a cursor resource. If this member is NULL, an application must explicitly set the cursor shape whenever the mouse moves into the application's window. */
	WindowClass.lpszClassName = "PMGameEngineClass";	/* If lpszClassName is a string, it specifies the window class name. The class name can be any name registered with RegisterClass or RegisterClassEx, or any of the predefined control-class names. */
	WindowClass.hIconSm = LoadIcon( 0, IDI_APPLICATION );	/* A handle to a small icon that is associated with the window class. If this member is NULL, the system searches the icon resource specified by the hIcon member for an icon of the appropriate size to use as the small icon. */
}

void win32_base::Initialize( WNDPROC WindowsProcedure, int16 Width, int16 Height )
{
	// Specifies the procedure callback to use for handling windows messages.
	WindowClass.lpfnWndProc = WindowsProcedure;

	// Adjust the client area, so that the window gets the right size and
	// matches the buffer.
	RECT WindowRect = { 0, 0, Width, Height };
	AdjustWindowRect( &WindowRect, WS_OVERLAPPEDWINDOW, FALSE );
	ClientRectWidth = WindowRect.right - WindowRect.left;
	ClientRectHeight = WindowRect.bottom - WindowRect.top;

	this->Width = Width;
	this->Height = Height;

	RegisterClassEx( &WindowClass );
}

void win32_base::ConstructWindow()
{
	// Create a window and get the handle:
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms632680(v=vs.85).aspx
	WindowHandle = CreateWindowEx( 0, WindowClass.lpszClassName, ApplicationName,
								   WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
								   ClientRectWidth, ClientRectHeight, 0, 0, GetModuleHandle( 0 ), 0 );

	// Sets the specified window's show state: 
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548(v=vs.85).aspx
	ShowWindow( WindowHandle, SW_SHOW );
}

LPCSTR win32_base::GetWindowClassName() const
{
	return WindowClass.lpszClassName;
}

HWND win32_base::GetWindowHandle() const
{
	return WindowHandle;
}

bool win32_base::GetIsRunning() const
{
	return IsRunning;
}

int16 win32_base::GetWidth() const
{
	return Width;
}

int16 win32_base::GetHeight() const
{
	return Height;
}

int16 win32_base::GetClientRectWidth() const
{
	return ClientRectWidth;
}

int16 win32_base::GetClientRectHeight() const
{
	return ClientRectHeight;
}

void win32_base::TerminateWindow()
{
	IsRunning = 0;
}