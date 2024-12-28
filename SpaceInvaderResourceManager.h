#pragma once
#include "ManagedSound.h"
#include "ManagedTexture.h"
#include <vector>
#include <string_view>
#include <unordered_map>

struct SpaceInvadersResourceManager
{
	SpaceInvadersResourceManager();

	ManagedSound hit_sound{ "./hitHurt.ogg" };

	const Texture2D& GetTexture2D(const std::string_view& path);

private:
	const void PreloadTexture(const std::string_view& path);
	std::unordered_map<std::string_view, ManagedTexture2D> textures;
};