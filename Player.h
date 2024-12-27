#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "AnimatedSprite.h"
#include "AnimatedSpriteRenderer.h"

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

	AnimatedSprite animated_sprite;
	AnimatedSpriteRenderer animated_sprite_renderer;

	EntityType type = EntityType::PLAYER;

	Player(SpaceInvadersResourceManager& resources);

	void Render(SpaceInvadersResourceManager& resources);
	void Update();

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
