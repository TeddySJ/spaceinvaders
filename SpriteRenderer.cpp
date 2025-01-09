#include "SpriteRenderer.h"

void SpriteRenderer::Render(const RaylibResourceManager& resources, const Sprite& sprite, Vector2 position) const
{
	constexpr float rotation = 0;
	DrawTexturePro(resources.GetTexture2D(sprite.texture_path),
		GetSpriteSourceRectangle(sprite),
		GetSpriteTargetRectangle(sprite, position),
		sprite.render_offset,
		rotation,
		WHITE);
}