#include "Wall.h"
#include <string>

Wall::Wall(Vector2 position) noexcept
	: position{ position }
{
}

void Wall::Render(const RaylibResourceManager& resources) const
{
	sprite_renderer.Render(resources, sprite, position);
	DrawText(std::to_string(health).data(), static_cast<int>(position.x - 21), static_cast<int>(position.y + 10), 40, RED);
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
