#include "Player.h"

Player::Player()
	: position{ static_cast<float>(GetScreenWidth() / 2) , GetScreenHeight() - player_base_height }
{
}

void Player::Render(Texture2D texture)
{
	float window_height = GetScreenHeight();

	DrawTexturePro(texture,
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x, window_height - player_base_height,
			100,
			100,
		}, { 50, 50 },
		0,
		WHITE);
}


void Player::Update()
{

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

	if (position.x < 0 + radius)
	{
		position.x = 0 + radius;
	}
	else if (position.x > GetScreenWidth() - radius)
	{
		position.x = GetScreenWidth() - radius;
	}


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
