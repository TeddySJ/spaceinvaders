#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"

struct Alien : ICollidable
{
public:

	Color color = WHITE;
	Vector2 position;
	float radius = 30;
	Vector2 collider_size{60, 30};
	int speed = 2;

	bool active = true;
	bool moveRight = true;

	EntityType type = EntityType::ENEMY;

	explicit Alien(Vector2 position) noexcept;

	void Update();
	void Render(Texture2D texture);

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
