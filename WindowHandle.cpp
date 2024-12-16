#include "raylib.h"
#include "WindowHandle.h"
#include <stdexcept>

RaylibWindowHandle::RaylibWindowHandle(int screenWidth, int screenHeight, const std::string_view& title)
{
	InitWindow(screenWidth, screenHeight, title.data());
	if (!IsWindowReady())
	{
		throw std::exception(); // TODO: Improve exception
	}
}

RaylibWindowHandle::~RaylibWindowHandle()
{
	CloseWindow();
}

void RaylibWindowHandle::SetTargetFPS(const int fps) const
{
	RLAPI::SetTargetFPS(fps);
}
