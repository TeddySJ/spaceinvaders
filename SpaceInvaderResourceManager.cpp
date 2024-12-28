#include "SpaceInvaderResourceManager.h"

SpaceInvadersResourceManager::SpaceInvadersResourceManager()
{
	LoadTexture("./Assets/Alien.png");
	LoadTexture("./Assets/ship_spritesheet.png");
	LoadTexture("./Assets/Barrier.png");
	LoadTexture("./Assets/Laser.png");
}

const Texture2D& SpaceInvadersResourceManager::GetTexture2D(const std::string_view& path) const
{
	return textures.at(path).GetTexture();
}

void SpaceInvadersResourceManager::LoadTexture(const std::string_view& path)
{
	textures.try_emplace(path, path);
}
