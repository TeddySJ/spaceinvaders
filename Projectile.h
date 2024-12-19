#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"

struct Projectile : ICollidable
{
public:
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position;
	int speed;
	bool active = true;
	EntityType type;

	Vector2 collider_size{ 10, 20 };

	// LINE WILL UPDATE WITH POSITION FOR CALCULATIONS
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	Projectile(Vector2 position, int speed, EntityType type);

	void Update();
	void Render(Texture2D texture);

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
