#include "Alien.h"


Alien::Alien(Vector2 position) noexcept
	:
	position{ position }
{
}

void Alien::Update()
{
	position.x += speed * x_direction;

	if (!IsInRange(position.x, 0, GetScreenWidth()))
	{
		MoveToNextRow();
	}
}

void Alien::MoveToNextRow()
{
	position.y += row_height;
	x_direction *= -1;
}

void Alien::Render(SpaceInvadersResourceManager& resources)
{
	sprite_renderer.Render(resources, sprite, position);
}	

Rectangle Alien::GetCollisionRect() const
{
	return { position.x - collider_size.x / 2, position.y - collider_size.y / 2, collider_size.x, collider_size.y };
}

void Alien::OnCollision()
{
	active = false;
}
