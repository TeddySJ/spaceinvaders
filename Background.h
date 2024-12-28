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

		Star() noexcept;
		void Render() const noexcept;
	};

	std::vector<Star> stars;

	explicit Background(size_t starAmount) noexcept;

	void Render() const noexcept;
};