#include "raylib.h"
#include "RaylibHandle.h"
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

RaylibAudioDeviceHandle::RaylibAudioDeviceHandle()
{
	InitAudioDevice();
	if (!IsAudioDeviceReady())
	{
		throw std::exception(); // TODO: Improve exception
	}
}

RaylibAudioDeviceHandle::~RaylibAudioDeviceHandle()
{
	CloseAudioDevice();
}

SpaceInvadersResourceHandler::SpaceInvadersResourceHandler()
{
	alien_texture = LoadTexture("./Assets/Alien.png");
	barrier_texture = LoadTexture("./Assets/Barrier.png");
	laser_texture = LoadTexture("./Assets/Laser.png");

	ship_textures.emplace_back(LoadTexture("./Assets/Ship1.png"));
	ship_textures.emplace_back(LoadTexture("./Assets/Ship2.png"));
	ship_textures.emplace_back(LoadTexture("./Assets/Ship3.png"));

	hit_sound = LoadSound("./hitHurt.ogg");
}

SpaceInvadersResourceHandler::~SpaceInvadersResourceHandler()
{
	UnloadTexture(alien_texture);
	UnloadTexture(barrier_texture);
	UnloadTexture(laser_texture);

	for (const auto& x : ship_textures)
		UnloadTexture(x);

	UnloadSound(hit_sound);
}
