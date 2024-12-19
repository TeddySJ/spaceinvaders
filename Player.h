#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"

struct Player : ICollidable
{
public:

	float player_base_height = 70.0f;
	Vector2 position;
	float speed = 7;
	Vector2 collider_size{ 60, 30 };
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	EntityType type = EntityType::PLAYER;

	Player();

	void Render(Texture2D texture);
	void Update();

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
