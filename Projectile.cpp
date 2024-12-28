#include "Projectile.h"

Projectile::Projectile(Vector2 position, int speed, EntityType type)
	: position{ position }, speed{ speed }, type{ type }
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

void Projectile::Render(SpaceInvadersResourceManager& resources)
{
	sprite_renderer.Render(resources, sprite, position);
}

Rectangle Projectile::GetCollisionRect() const
{
	return { position.x - collider_size.x / 2, position.y - collider_size.y / 2, collider_size.x, collider_size.y };
}

void Projectile::OnCollision()
{
	active = false;
}
