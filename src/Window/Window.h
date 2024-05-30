#pragma once

#include <windows.h>
#include "InputDevice.h"

class InputDevice;

class Window
{
 private:
	HINSTANCE hInstance;
	HWND hWnd;
	LONG height;
	LONG width;

 public:
	Window(LPCSTR name, LONG width, LONG height);
	[[nodiscard]] LONG getWidth() const;
	[[nodiscard]] LONG getHeight() const;
	HWND getHWnd();
};
