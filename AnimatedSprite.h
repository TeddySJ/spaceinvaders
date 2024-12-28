#pragma once

#include "Sprite.h"

class AnimatedSprite final : public Sprite
{
public: 
	Vector2 cell_size;
	uint16_t frames;
	double time_per_frame;
	AnimatedSprite(const std::string_view& texture_path, Vector2 texture_size, Vector2 render_size, Vector2 render_offset, uint16_t frames, double time_per_frame) noexcept;
};

uint16_t GetAnimatedSpriteFrame(const AnimatedSprite& animated_sprite, double time_passed) noexcept;

Rectangle GetAnimatedSpriteSourceRectangle(const AnimatedSprite& animated_sprite, uint16_t frame) noexcept;