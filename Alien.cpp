#include "Alien.h"

static constexpr Vector2 RENDER_SIZE{ 100, 100 };
static constexpr Vector2 RENDER_OFFSET{ 50, 50 };
static constexpr std::string_view ALIEN_TEXTURE_PATH = "./Assets/Alien.png";

Alien::Alien(SpaceInvadersResourceManager& resources, Vector2 position) noexcept
	:
	position{ position }, 
	sprite{ ALIEN_TEXTURE_PATH, GetTextureSizeFromPath(resources, ALIEN_TEXTURE_PATH), RENDER_SIZE, RENDER_OFFSET }
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
	SpriteRenderer::Render(resources, sprite, position);
}	

Rectangle Alien::GetCollisionRect() const
{
	return { position.x - collider_size.x / 2, position.y - collider_size.y / 2, collider_size.x, collider_size.y };
}

void Alien::OnCollision()
{
	active = false;
}
