#pragma once
#include "AnimatedSprite.h"

class AnimatedSpriteRenderer
{
public:
	uint16_t current_frame;
	double time_accumulated;

	void Update(const AnimatedSprite& sprite, double delta_time)
	{
		time_accumulated += delta_time;
		while (time_accumulated >= sprite.time_per_frame)
		{
			current_frame = (current_frame + 1) % sprite.frames;
			time_accumulated -= sprite.time_per_frame;
		}
	}

	void Render(SpaceInvadersResourceManager& resources, const AnimatedSprite& sprite, Vector2 position)
	{
		DrawTexturePro(resources.GetTexture2D(sprite.texture_path),
			sprite.GetSourceRectangle(current_frame),
			GetSpriteTargetRectangle(sprite, position),
			sprite.render_offset,
			0,
			WHITE);
	}
};