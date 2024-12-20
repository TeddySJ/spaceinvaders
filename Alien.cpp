#include "Alien.h"

static constexpr Vector2 RENDER_SIZE{ 100, 100 };
static constexpr Vector2 RENDER_OFFSET{ 50, 50 };

Alien::Alien(SpaceInvadersResourceManager& resources, Vector2 position) noexcept
	:
	position{ position }, 
	animation{ resources, "./Assets/Alien.png", RENDER_SIZE, RENDER_OFFSET }
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
	animation.Render(resources, position);
}

Rectangle Alien::GetCollisionRect() const
{
	return { position.x - collider_size.x / 2, position.y - collider_size.y / 2, collider_size.x, collider_size.y };
}

void Alien::OnCollision()
{
	active = false;
}
