#pragma once

#include <windows.h>
#include "InputDevice.h"

class Window
{
 private:
	HINSTANCE _hInstance;
	HWND _hWnd;
	LONG _height;
	LONG _width;

 public:
	Window(LPCSTR name, LONG width, LONG height);
	[[nodiscard]] LONG getWidth() const { return _width; };
	[[nodiscard]] LONG getHeight() const { return _height; };
	[[nodiscard]] HWND getHWnd() const { return _hWnd; };
	[[nodiscard]] float GetRatio() const { return static_cast<float>(_width) / static_cast<float>(_height); }
};
