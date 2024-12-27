#include "Projectile.h"

static constexpr Vector2 RENDER_SIZE{ 50, 50};
static constexpr Vector2 RENDER_OFFSET{ 25, 25 };
static constexpr std::string_view PROJECTILE_TEXTURE_PATH = "./Assets/Laser.png";

Projectile::Projectile(SpaceInvadersResourceManager& resources, Vector2 position, int speed, EntityType type)
	: position{ position },
	sprite{ PROJECTILE_TEXTURE_PATH, GetTextureSizeFromPath(resources, PROJECTILE_TEXTURE_PATH), RENDER_SIZE, RENDER_OFFSET },
	speed{ speed }, type{ type }
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
