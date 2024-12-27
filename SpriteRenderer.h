#pragma once
#include "Sprite.h"

class SpriteRenderer
{
public:
	void Render(SpaceInvadersResourceManager& resources, const Sprite& sprite, Vector2 position) const;
};