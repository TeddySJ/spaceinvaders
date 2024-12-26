#include "Sprite.h"

Sprite::Sprite(const std::string_view& texture_path, Vector2 texture_size, Vector2 render_size, Vector2 render_offset)
	: texture_path{ texture_path }, texture_size{ texture_size }, render_size{ render_size }, render_offset{ render_offset }
{
}

Rectangle GetSpriteSourceRectangle(const Sprite& sprite)
{
	return { 0, 0, sprite.texture_size.x, sprite.texture_size.y };
}

Rectangle GetSpriteTargetRectangle(const Sprite& sprite, Vector2 position)
{
	return { position.x, position.y, sprite.render_size.x, sprite.render_size.y };
}

Vector2 GetTextureSizeFromLoadedTexture(const Texture2D& texture)
{
	return { static_cast<float>(texture.width), static_cast<float>(texture.height) };
}

Vector2 GetTextureSizeFromPath(SpaceInvadersResourceManager& resources, const std::string_view& texture_path)
{
	return GetTextureSizeFromLoadedTexture(resources.GetTexture2D(texture_path));
}
