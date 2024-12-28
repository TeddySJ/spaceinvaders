#include "SpaceInvaderResourceManager.h"

SpaceInvadersResourceManager::SpaceInvadersResourceManager()
{
	PreloadTexture("./Assets/Alien.png");
	PreloadTexture("./Assets/ship_spritesheet.png");
	PreloadTexture("./Assets/Barrier.png");
	PreloadTexture("./Assets/Laser.png");
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
