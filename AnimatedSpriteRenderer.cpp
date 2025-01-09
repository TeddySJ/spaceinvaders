#include "AnimatedSpriteRenderer.h"

void AnimatedSpriteRenderer::Render(const RaylibResourceManager& resources, const AnimatedSprite& sprite, Vector2 position) const
{
	const float rotation = 0;
	DrawTexturePro(resources.GetTexture2D(sprite.texture_path),
		GetAnimatedSpriteSourceRectangle(sprite, current_frame),
		GetSpriteTargetRectangle(sprite, position),
		sprite.render_offset,
		rotation,
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