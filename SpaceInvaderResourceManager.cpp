#include "SpaceInvaderResourceManager.h"

const Texture2D& RaylibResourceManager::GetTexture2D(const std::string_view& path) const
{
	return textures.at(path).GetTexture();
}

void RaylibResourceManager::LoadTexture(const std::string_view& path)
{
	textures.try_emplace(path, path);
}
