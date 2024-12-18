#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"

struct Alien
{
public:

	Color color = WHITE;
	Vector2 position;
	float radius = 30;
	bool active = true;
	bool moveRight = true;

	EntityType type = EntityType::ENEMY;

	int speed = 2;

	explicit Alien(Vector2 position) noexcept;

	void Update();
	void Render(Texture2D texture);
};
