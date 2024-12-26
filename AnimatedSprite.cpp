#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const std::string_view& texture_path, Vector2 texture_size, Vector2 render_size, Vector2 render_offset, Vector2 cell_size, uint16_t frames, double time_per_frame)
	: Sprite{ texture_path , texture_size ,render_size, render_offset }, cell_size{ cell_size },  frames{ frames }, time_per_frame{ time_per_frame }
{
}
