#include "Wall.h"

Wall::Wall(Vector2 position)
	: position{ position }
{
}

void Wall::Render(const SpaceInvadersResourceManager& resources) const
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