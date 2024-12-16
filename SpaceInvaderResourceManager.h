#pragma once
#include "ManagedSound.h"
#include "ManagedTexture.h"
#include <vector>

struct SpaceInvadersResourceManager
{
	SpaceInvadersResourceManager();

	std::vector<ManagedTexture2D> ship_textures{};

	ManagedTexture2D alien_texture{ "./Assets/Alien.png" };
	ManagedTexture2D barrier_texture{ "./Assets/Barrier.png" };
	ManagedTexture2D laser_texture{ "./Assets/Laser.png" };

	ManagedSound hit_sound{ "./hitHurt.ogg" };
};