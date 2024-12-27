#include "Player.h"
#include <algorithm>

static constexpr Vector2 RENDER_SIZE{ 100, 100 };
static constexpr Vector2 RENDER_OFFSET{ 50, 50 };
static constexpr std::string_view PLAYER_TEXTURE_PATH = "./Assets/ship_spritesheet.png";

Player::Player(SpaceInvadersResourceManager& resources)
	: position{ static_cast<float>(GetScreenWidth() / 2) , GetScreenHeight() - player_base_height },
	animated_sprite{ PLAYER_TEXTURE_PATH, GetTextureSizeFromPath(resources, PLAYER_TEXTURE_PATH), RENDER_SIZE, RENDER_OFFSET, 3, 0.1  }
{
}

void Player::Render(SpaceInvadersResourceManager& resources)
{
	animated_sprite_renderer.Render(resources, animated_sprite, position);
}

void Player::Update()
{
	animated_sprite_renderer.Update(animated_sprite, target_time_per_frame);

	//Movement
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	position.x += speed * direction;

	const auto half_collider = collider_size.x / 2;
	position.x = std::clamp(position.x, 0 + half_collider, GetScreenWidth() - half_collider);


	//Determine frame for animation
	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}


}

Rectangle Player::GetCollisionRect() const
{
	return { position.x - collider_size.x / 2, position.y - collider_size.y / 2, collider_size.x, collider_size.y };
}


void Player::OnCollision()
{
	lives--;
}
