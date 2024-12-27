#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

struct Wall : ICollidable
{
public:
	Vector2 position;
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;

	Sprite sprite;
	SpriteRenderer sprite_renderer;

	Vector2 collider_size{ 140, 20 };

	Wall(SpaceInvadersResourceManager& resources, Vector2 position);

	void Render(SpaceInvadersResourceManager& resources);
	void Update();

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
