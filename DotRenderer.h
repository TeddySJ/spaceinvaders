#pragma once
#include "raylib.h"

class DotRenderer
{
public:
	static void Render(Vector2 position, float size)
	{
		DrawTexturePro(resources.GetTexture2D(sprite.texture_path),
			GetSpriteSourceRectangle(sprite),
			GetSpriteTargetRectangle(sprite, position),
			sprite.render_offset,
			0,
			WHITE);
	}
};