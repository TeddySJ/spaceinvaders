#pragma once
#include "raylib.h"

class RaylibAudioDeviceHandle
{
public:
	RaylibAudioDeviceHandle();
	~RaylibAudioDeviceHandle();

	RaylibAudioDeviceHandle(const RaylibAudioDeviceHandle&) = delete;
	RaylibAudioDeviceHandle& operator=(const RaylibAudioDeviceHandle&) = delete;

	RaylibAudioDeviceHandle(RaylibAudioDeviceHandle&&) = default;
	RaylibAudioDeviceHandle& operator=(RaylibAudioDeviceHandle&&) = default;
};