#include "raylib.h"
#include "WindowHandle.h"
#include <stdexcept>
#include "CustomExceptions.h"

RaylibWindowHandle::RaylibWindowHandle(int screenWidth, int screenHeight, std::string_view title)
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

void RaylibWindowHandle::SetTargetFPS(int fps) const noexcept
{
	RLAPI::SetTargetFPS(fps);
}
