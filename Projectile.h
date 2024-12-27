#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

struct Projectile : ICollidable
{
public:
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position;
	int speed;
	bool active = true;
	EntityType type;

	Sprite sprite;
	SpriteRenderer sprite_renderer;

	Vector2 collider_size{ 10, 20 };

	Projectile(SpaceInvadersResourceManager& resources, Vector2 position, int speed, EntityType type);

	void Update();
	void Render(SpaceInvadersResourceManager& resources);

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
