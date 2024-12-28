#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include <vector>

class Background final
{
public:
	explicit Background(size_t starAmount) noexcept;
	void Render() const noexcept;

private:
	struct Star
	{
		Vector2 position;
		float size;
		Color color = SKYBLUE;

		Star() noexcept;
		void Render() const noexcept;
	};

	std::vector<Star> stars;

};