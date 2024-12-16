#include "SpaceInvaderResourceManager.h"

SpaceInvadersResourceManager::SpaceInvadersResourceManager()
{
	ship_textures.reserve(3);
	ship_textures.emplace_back("./Assets/Ship1.png");
	ship_textures.emplace_back("./Assets/Ship2.png");
	ship_textures.emplace_back("./Assets/Ship3.png");
}