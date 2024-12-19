#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include <vector>

struct Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = SKYBLUE;
	float size = 0;

	Star();

	void Render();
};

struct Background
{
	std::vector<Star> stars;

	explicit Background(size_t starAmount);

	void Update(float offset);
	void Render();
};