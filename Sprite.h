#pragma once

#include "raylib.h"
#include "SpaceInvaderResourceManager.h"
#include "SpaceInvadersDefinitions.h"

class Sprite
{
public:
	Sprite(const std::string_view& texture_path, Vector2 texture_size, Vector2 render_size, Vector2 render_offset) noexcept;

	std::string_view texture_path;
	Vector2 texture_size;
	Vector2 render_size;
	Vector2 render_offset;
};

Rectangle GetSpriteSourceRectangle(const Sprite& sprite) noexcept;

Rectangle GetSpriteTargetRectangle(const Sprite& sprite, Vector2 position) noexcept;
