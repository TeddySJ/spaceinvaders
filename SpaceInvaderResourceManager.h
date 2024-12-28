#pragma once
#include "ManagedSound.h"
#include "ManagedTexture.h"
#include <vector>
#include <string_view>
#include <unordered_map>

class SpaceInvadersResourceManager
{
public:
	SpaceInvadersResourceManager();

	const Texture2D& GetTexture2D(const std::string_view& path) const;
	void LoadTexture(const std::string_view& path);

private:
	std::unordered_map<std::string_view, ManagedTexture2D> textures;
	ManagedSound hit_sound{ "./hitHurt.ogg" };

};