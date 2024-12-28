#pragma once
#include "raylib.h"

class RaylibAudioDeviceHandle final
{
public:
	RaylibAudioDeviceHandle();
	~RaylibAudioDeviceHandle();

	RaylibAudioDeviceHandle(const RaylibAudioDeviceHandle&) = delete;
	RaylibAudioDeviceHandle& operator=(const RaylibAudioDeviceHandle&) = delete;

	RaylibAudioDeviceHandle(RaylibAudioDeviceHandle&&) = default;
	RaylibAudioDeviceHandle& operator=(RaylibAudioDeviceHandle&&) = default;
};