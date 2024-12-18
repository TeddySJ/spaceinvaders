#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"

struct Wall
{
public:
	Vector2 position;
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;
	int radius = 60;

	explicit Wall(Vector2 position);

	void Render(Texture2D texture);
	void Update();
};
