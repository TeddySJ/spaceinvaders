#include "Wall.h"

static constexpr Vector2 RENDER_SIZE{ 200, 200 };
static constexpr Vector2 RENDER_OFFSET{ 100, 100 };
static constexpr std::string_view PROJECTILE_TEXTURE_PATH = "./Assets/Barrier.png";

Wall::Wall(SpaceInvadersResourceManager& resources, Vector2 position)
	: position{ position },
	sprite{ PROJECTILE_TEXTURE_PATH, GetTextureSizeFromPath(resources, PROJECTILE_TEXTURE_PATH), RENDER_SIZE, RENDER_OFFSET }
{
}

void Wall::Render(SpaceInvadersResourceManager& resources)
{
	sprite_renderer.Render(resources, sprite, position);
	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED); // TODO: Use std::format
}

Rectangle Wall::GetCollisionRect() const
{
	return { position.x - collider_size.x / 2, position.y - collider_size.y / 2, collider_size.x, collider_size.y };
}

void Wall::OnCollision()
{
	if (--health == 0)
	{
		active = false;
	}
}