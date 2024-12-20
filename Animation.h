#pragma once

#include "raylib.h"
#include "SpaceInvaderResourceManager.h"
#include "SpaceInvadersDefinitions.h"

class Animation
{
	Vector2 cell_size;
	Vector2 render_size;
	Vector2 render_offset;

	Rectangle texture_size;
	std::string_view texture_path;

	uint16_t frames;
	uint16_t ticks_per_frame;

	Rectangle GetSourceRectangle(uint16_t ticks) const
	{
		if (frames == 1)
			return texture_size;

		int frame_to_use = (ticks / ticks_per_frame) % frames;
		Vector2 frame_size = { (texture_size.x / frames), texture_size.y };
		return { frame_size.x * frame_to_use, 0, frame_size.x, frame_size.y };
	}

public: 
	Animation(SpaceInvadersResourceManager& resources, const std::string_view& texture_path, Vector2 render_size, Vector2 render_offset);
	Animation(SpaceInvadersResourceManager& resources, const std::string_view& texture_path, Vector2 render_size, Vector2 render_offset, uint16_t frames, uint16_t ticks_per_frame);

	void Render(SpaceInvadersResourceManager& resources, Vector2 position, uint16_t ticks = 1) const;
};