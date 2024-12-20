#pragma once
#include "ManagedSound.h"
#include "ManagedTexture.h"
#include <vector>
#include <string_view>
#include <unordered_map>

struct SpaceInvadersResourceManager
{
	SpaceInvadersResourceManager();

	std::vector<ManagedTexture2D> ship_textures{};

	ManagedTexture2D alien_texture{ "./Assets/Alien.png" };
	ManagedTexture2D barrier_texture{ "./Assets/Barrier.png" };
	ManagedTexture2D laser_texture{ "./Assets/Laser.png" };

	ManagedSound hit_sound{ "./hitHurt.ogg" };

	const Texture2D& GetTexture2D(const std::string_view& path);

private:
	const void PreloadTexture(const std::string_view& path);
	std::unordered_map<std::string_view, ManagedTexture2D> textures;
};