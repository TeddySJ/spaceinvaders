#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"

struct Wall : ICollidable
{
public:
	Vector2 position;
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;
	int radius = 60;

	Vector2 collider_size{ 140, 20 };

	explicit Wall(Vector2 position);

	void Render(Texture2D texture);
	void Update();

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
