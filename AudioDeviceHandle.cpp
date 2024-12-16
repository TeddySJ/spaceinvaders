#include "AudioDeviceHandle.h"
#include <stdexcept>

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
