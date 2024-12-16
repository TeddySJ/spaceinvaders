#pragma once

#include "raylib.h"
#include <string_view>

class RaylibWindowHandle
{

	RaylibWindowHandle(const RaylibWindowHandle&) = delete;
	RaylibWindowHandle& operator=(const RaylibWindowHandle&) = delete;

	RaylibWindowHandle(RaylibWindowHandle&&) = default;
	RaylibWindowHandle& operator=(RaylibWindowHandle&&) = default;

public:
	RaylibWindowHandle(int screenWidth, int screenHeight, const std::string_view& title);
	~RaylibWindowHandle();

	void SetTargetFps(int fps) const;
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