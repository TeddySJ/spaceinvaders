#include "Animation.h"

Animation::Animation(SpaceInvadersResourceManager& resources, const std::string_view& texture_path, Vector2 render_size, Vector2 render_offset)
	: texture_path{ texture_path }, render_size{ render_size }, render_offset{ render_offset }, frames{ 1 }, ticks_per_frame{ 1 }
{
	Texture2D texture = resources.GetTexture2D(texture_path);
	texture_size = GetTextureBoundsAsRectangle(texture);
}

Animation::Animation(SpaceInvadersResourceManager& resources, const std::string_view& texture_path, Vector2 render_size, Vector2 render_offset, uint16_t frames, uint16_t ticks_per_frame)
	: texture_path{ texture_path }, render_size{ render_size }, render_offset{ render_offset }, frames{ frames }, ticks_per_frame{ ticks_per_frame }
{
	Texture2D texture = resources.GetTexture2D(texture_path);
	texture_size = GetTextureBoundsAsRectangle(texture);
}

void Animation::Render(SpaceInvadersResourceManager& resources, Vector2 position, uint16_t ticks) const
{
	DrawTexturePro(resources.GetTexture2D(texture_path),
		GetSourceRectangle(ticks),
		{
			position.x,
			position.y,
			render_size.x,
			render_size.y,
		},
		{ render_offset.x , render_offset.y },
		0,
		WHITE);
}
