#include "Background.h"

Star::Star()
{
	// TODO: Replace with a playfield rect
	position.x = GetRandomValue(-150, GetScreenWidth() + 150);
	position.y = GetRandomValue(0, GetScreenHeight());

	//random color?
	// TODO: Implement random color, chosen from a set of static constexpr colors defined in Star.h
	color = SKYBLUE;

	size = GetRandomValue(1, 4) / 2;
}

void Star::Render()
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}

Background::Background(size_t starAmount)
	: stars{starAmount}
{
	// TODO: Since the background is static, could this whole setup be constexpr?
}

void Background::Update(float offset)
{
	// TODO: Update will be removed both from here and Render)
	
}

void Background::Render()
{
	// TODO: Replace with algorithm
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i].Render();
	}
}

