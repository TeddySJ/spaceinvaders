#include "AnimatedSpriteRenderer.h"

void AnimatedSpriteRenderer::Render(const SpaceInvadersResourceManager& resources, const AnimatedSprite& sprite, Vector2 position) const
{
	DrawTexturePro(resources.GetTexture2D(sprite.texture_path),
		GetAnimatedSpriteSourceRectangle(sprite, current_frame),
		GetSpriteTargetRectangle(sprite, position),
		sprite.render_offset,
		0,
		WHITE);
}

void AnimatedSpriteRenderer::Update(const AnimatedSprite& sprite, double delta_time) noexcept
{
	time_accumulated += delta_time;
	while (time_accumulated >= sprite.time_per_frame)
	{
		current_frame = (current_frame + 1) % sprite.frames;
		time_accumulated -= sprite.time_per_frame;
	}
}