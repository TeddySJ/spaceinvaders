#include "Player.h"
#include <algorithm>


Player::Player() noexcept
	: playfield_rect{ SpaceInvaderUtils::GetPlayfieldRectangle()}
{
	position = { playfield_rect.x + playfield_rect.width / 2, SpaceInvaderUtils::RectBottom(playfield_rect) - PLAYER_DISTANCE_FROM_BOTTOM};
}

void Player::Render(const SpaceInvadersResourceManager& resources) const
{
	animated_sprite_renderer.Render(resources, animated_sprite, position);
}

void Player::Update()
{
	animated_sprite_renderer.Update(animated_sprite, SpaceInvaderUtils::target_time_per_frame);

	position.x += PLAYER_SPEED * direction;

	const auto half_collider = COLLIDER_SIZE.x / 2;
	position.x = std::clamp(position.x, playfield_rect.x + half_collider, SpaceInvaderUtils::RectRight(playfield_rect) - half_collider);
}

void Player::SetDirection(float new_direction) noexcept
{
	direction = new_direction;
}

Rectangle Player::GetCollisionRect() const noexcept
{
	return { position.x - COLLIDER_SIZE.x / 2, position.y - COLLIDER_SIZE.y / 2, COLLIDER_SIZE.x, COLLIDER_SIZE.y };
}


void Player::OnCollision() noexcept
{
	lives -= 1;
}
