#include "SpaceInvaderResourceManager.h"

SpaceInvadersResourceManager::SpaceInvadersResourceManager()
{
	ship_textures.reserve(3);
	ship_textures.emplace_back("./Assets/Ship1.png");
	ship_textures.emplace_back("./Assets/Ship2.png");
	ship_textures.emplace_back("./Assets/Ship3.png");

	PreloadTexture("./Assets/Alien.png");
}

const Texture2D& SpaceInvadersResourceManager::GetTexture2D(const std::string_view& path)
{
	auto [it, inserted] = textures.try_emplace(path, path);
	return it->second.GetTexture();
}

const void SpaceInvadersResourceManager::PreloadTexture(const std::string_view& path)
{
	textures.try_emplace(path, path);
}
