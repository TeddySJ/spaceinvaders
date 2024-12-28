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

	const Texture2D& GetTexture2D(const std::string_view& path) const;
	void LoadTexture(const std::string_view& path);

private:
	std::unordered_map<std::string_view, ManagedTexture2D> textures;
};