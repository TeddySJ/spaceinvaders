#pragma once
#include "Sprite.h"

class SpriteRenderer
{
public:
	static void Render(SpaceInvadersResourceManager& resources, const Sprite& sprite, Vector2 position)
	{
		DrawTexturePro(resources.GetTexture2D(sprite.texture_path),
			GetSpriteSourceRectangle(sprite),
			GetSpriteTargetRectangle(sprite, position),
			sprite.render_offset,
			0,
			WHITE);
	}
};