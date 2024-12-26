#pragma once

#include "raylib.h"
#include "SpaceInvaderResourceManager.h"
#include "SpaceInvadersDefinitions.h"

class Sprite
{
public:
	Sprite(const std::string_view& texture_path, Vector2 texture_size, Vector2 render_size, Vector2 render_offset);

	std::string_view texture_path;
	Vector2 texture_size;
	Vector2 render_size;
	Vector2 render_offset;
};

Rectangle GetSpriteSourceRectangle(const Sprite& sprite);

Rectangle GetSpriteTargetRectangle(const Sprite& sprite, Vector2 position);

Vector2 GetTextureSizeFromLoadedTexture(const Texture2D& texture);

Vector2 GetTextureSizeFromPath(SpaceInvadersResourceManager& resources, const std::string_view& texture_path);