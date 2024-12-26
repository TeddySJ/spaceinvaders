#pragma once

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public: 
	Vector2 cell_size;
	uint16_t frames;
	double time_per_frame;

	uint16_t GetFrame(double time_passed) const
	{
		return static_cast<uint16_t>(floor(time_passed / time_per_frame)) % frames;
	}

	Rectangle GetSourceRectangle(uint16_t frame) const
	{
		Vector2 frame_size = { (texture_size.x / frames), texture_size.y };
		return { frame_size.x * frame, 0, frame_size.x, frame_size.y };
	}

public: 
	AnimatedSprite(const std::string_view& texture_path, Vector2 texture_size, Vector2 render_size, Vector2 render_offset, Vector2 cell_size, uint16_t frames, double time_per_frame);
};