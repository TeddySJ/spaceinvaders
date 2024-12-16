#pragma once

#include "raylib.h"
#include <string_view>
#include <vector>

class RaylibWindowHandle
{

	RaylibWindowHandle(const RaylibWindowHandle&) = delete;
	RaylibWindowHandle& operator=(const RaylibWindowHandle&) = delete;

	RaylibWindowHandle(RaylibWindowHandle&&) = default;
	RaylibWindowHandle& operator=(RaylibWindowHandle&&) = default;

public:
	RaylibWindowHandle(int screenWidth, int screenHeight, const std::string_view& title);
	~RaylibWindowHandle();

	void SetTargetFPS(int fps) const;
};

class RaylibAudioDeviceHandle
{
	RaylibAudioDeviceHandle(const RaylibAudioDeviceHandle&) = delete;
	RaylibAudioDeviceHandle& operator=(const RaylibAudioDeviceHandle&) = delete;

	RaylibAudioDeviceHandle(RaylibAudioDeviceHandle&&) = default;
	RaylibAudioDeviceHandle& operator=(RaylibAudioDeviceHandle&&) = default;

public:
	RaylibAudioDeviceHandle();
	~RaylibAudioDeviceHandle();

};

class SpaceInvadersResourceHandler
{
	SpaceInvadersResourceHandler(const SpaceInvadersResourceHandler&) = delete;
	SpaceInvadersResourceHandler& operator=(const SpaceInvadersResourceHandler&) = delete;

	SpaceInvadersResourceHandler(SpaceInvadersResourceHandler&&) = default;
	SpaceInvadersResourceHandler& operator=(SpaceInvadersResourceHandler&&) = default;

public:
	SpaceInvadersResourceHandler();
	~SpaceInvadersResourceHandler();

	std::vector<Texture2D> ship_textures;
	Texture2D alien_texture;
	Texture2D barrier_texture;
	Texture2D laser_texture;

	Sound hit_sound;
};