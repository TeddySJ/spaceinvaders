#pragma once

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public: 
	Vector2 cell_size;
	uint16_t frames;
	double time_per_frame;

public: 
	AnimatedSprite(const std::string_view& texture_path, Vector2 texture_size, Vector2 render_size, Vector2 render_offset, Vector2 cell_size, uint16_t frames, double time_per_frame);
};

uint16_t GetAnimatedSpriteFrame(const AnimatedSprite& animated_sprite, double time_passed);

Rectangle GetAnimatedSpriteSourceRectangle(const AnimatedSprite& animated_sprite, uint16_t frame);