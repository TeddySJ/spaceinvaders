#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const std::string_view& texture_path, Vector2 texture_size, Vector2 render_size, Vector2 render_offset, Vector2 cell_size, uint16_t frames, double time_per_frame)
	: Sprite{ texture_path , texture_size ,render_size, render_offset }, cell_size{ cell_size },  frames{ frames }, time_per_frame{ time_per_frame }
{
}

uint16_t GetAnimatedSpriteFrame(const AnimatedSprite& animated_sprite, double time_passed)
{
	return static_cast<uint16_t>(floor(time_passed / animated_sprite.time_per_frame)) % animated_sprite.frames;
}

Rectangle GetAnimatedSpriteSourceRectangle(const AnimatedSprite& animated_sprite, uint16_t frame)
{
	Vector2 frame_size = { (animated_sprite.texture_size.x / animated_sprite.frames), animated_sprite.texture_size.y };
	return { frame_size.x * frame, 0, frame_size.x, frame_size.y };
}