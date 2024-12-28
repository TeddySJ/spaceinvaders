#include "raylib.h"
#include "WindowHandle.h"
#include <stdexcept>
#include "CustomExceptions.h"

RaylibWindowHandle::RaylibWindowHandle(int screenWidth, int screenHeight, const std::string_view& title)
{
	InitWindow(screenWidth, screenHeight, title.data());
	if (!IsWindowReady())
	{
		throw RaylibWindowCreationError();
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
