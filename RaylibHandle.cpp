#include "raylib.h"
#include "RaylibHandle.h"

RaylibWindowHandle::RaylibWindowHandle(int screenWidth, int screenHeight, const std::string_view& title)
{
	InitWindow(screenWidth, screenHeight, title.data());
}

RaylibWindowHandle::~RaylibWindowHandle()
{
	CloseWindow();
}

void RaylibWindowHandle::SetTargetFPS(const int fps) const
{
	RLAPI::SetTargetFPS(fps);
}

RaylibAudioDeviceHandle::RaylibAudioDeviceHandle()
{
	InitAudioDevice();
}

RaylibAudioDeviceHandle::~RaylibAudioDeviceHandle()
{
	CloseAudioDevice();
}
