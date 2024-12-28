#include "Projectile.h"

Projectile::Projectile(Vector2 position, float speed) noexcept
	: position{ position }, speed{ speed }
{
}

void Projectile::Update()
{
	position.y += speed;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(const SpaceInvadersResourceManager& resources) const
{
	sprite_renderer.Render(resources, sprite, position);
}

Rectangle Projectile::GetCollisionRect() const noexcept
{
	return { position.x - COLLIDER_SIZE.x / 2, position.y - COLLIDER_SIZE.y / 2, COLLIDER_SIZE.x, COLLIDER_SIZE.y };
}

void Projectile::OnCollision() noexcept
{
	active = false;
}

bool Projectile::IsActive() const noexcept
{
	return active;
}
