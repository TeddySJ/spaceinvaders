#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"

struct Player : ICollidable
{
public:

	Vector2 position;
	float speed = 7;
	float player_base_height = 70.0f;
	Vector2 size{ 50, 30 };
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	EntityType type = EntityType::PLAYER;

	Player();

	void Render(Texture2D texture);
	void Update();

	Rectangle GetCollisionRect() const override { return { position.x - size.x / 2, position.y - size.y / 2, size.x, size.y }; }
	void OnCollision() override { lives--; }
};
