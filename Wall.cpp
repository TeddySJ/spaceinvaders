#include "Wall.h"

Wall::Wall(Vector2 position) noexcept
	: position{ position }
{
}

void Wall::Render(const SpaceInvadersResourceManager& resources) const
{
	sprite_renderer.Render(resources, sprite, position);
	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED); // TODO: Use std::format
}

Rectangle Wall::GetCollisionRect() const noexcept
{
	return { position.x - COLLIDER_SIZE.x / 2, position.y - COLLIDER_SIZE.y / 2, COLLIDER_SIZE.x, COLLIDER_SIZE.y };
}

void Wall::OnCollision() noexcept
{
	--health;
}

bool Wall::IsActive() const noexcept
{
	return health > 0;
}
