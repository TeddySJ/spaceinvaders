#include "ManagedSound.h"
#include <stdexcept>

const Sound& ManagedSound::GetSound() const noexcept
{
	return sound;
}

ManagedSound::ManagedSound(std::string_view path)
{
	sound = LoadSound(path.data());

	if (sound.frameCount <= 0)
	{
		throw std::exception(); // TODO: Improve exception
	}
}

ManagedSound::~ManagedSound()
{
	UnloadSound(sound);
}