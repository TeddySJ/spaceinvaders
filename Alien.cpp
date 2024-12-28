#include "Alien.h"


Alien::Alien(Vector2 position) noexcept
	:
	position{ position }
{
}

void Alien::Update() noexcept
{
	position.x += speed * x_direction;

	if (!SpaceInvaderUtils::IsInRange(position.x, 0, GetScreenWidth()))
	{
		MoveToNextRow();
	}
}

void Alien::MoveToNextRow() noexcept
{
	position.y += row_height;
	x_direction *= -1;
}

void Alien::Render(const SpaceInvadersResourceManager& resources) const
{
	sprite_renderer.Render(resources, sprite, position);
}	

Rectangle Alien::GetCollisionRect() const noexcept
{
	return { position.x - collider_size.x / 2, position.y - collider_size.y / 2, collider_size.x, collider_size.y };
}

void Alien::OnCollision() noexcept
{
	--health;
}

bool Alien::IsActive() const noexcept
{
	return health > 0;
}

Vector2 Alien::GetPosition() const noexcept
{
	return position;
}
