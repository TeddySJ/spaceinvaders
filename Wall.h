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

	Vector2 size{ 60, 30 };

	explicit Wall(Vector2 position);

	void Render(Texture2D texture);
	void Update();

	Rectangle GetCollisionRect() const override { return { position.x - size.x / 2, position.y - size.y / 2, size.x, size.y }; }
	void OnCollision() override { active = false; }
};
