#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include <vector>

struct Background
{
	struct Star
	{
		Vector2 position;
		float size;
		Color color = SKYBLUE;

		Star();
		void Render() const;
	};

	std::vector<Star> stars;

	explicit Background(size_t starAmount);

	void Render() const;
};