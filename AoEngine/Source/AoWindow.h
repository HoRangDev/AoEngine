#pragma once
#include <string>
#include <stdint.h>
#include "WindowsInc.h"
using string = std::wstring;

class AoWindow
{
public:
	AoWindow( string Name, uint32_t Width, uint32_t Height );
	AoWindow();

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	HWND GetHandle() const;

private:
	static uint32_t DefaultWidth, DefaultHeight;
	uint32_t Width, Height;
	string Name;

	HWND Handle;

};