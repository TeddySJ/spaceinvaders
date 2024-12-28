#pragma once
#include "Sprite.h"

class SpriteRenderer final
{
public:
	void Render(const SpaceInvadersResourceManager& resources, const Sprite& sprite, Vector2 position) const;
};