#include "Background.h"

Star::Star()
{
	// TODO: Replace with a playfield rect
	initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
	initPosition.y = GetRandomValue(0, GetScreenHeight());

	//random color?
	// TODO: Implement random color, chosen from a set of static constexpr colors defined in Star.h
	color = SKYBLUE;

	size = GetRandomValue(1, 4) / 2;
}

void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;
}

void Star::Render()
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}

Background::Background(size_t starAmount)
	: stars{starAmount}
{
}

void Background::Update(float offset)
{
	// TODO: Replace with algorithm
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i].Update(offset);
	}
}

void Background::Render()
{
	// TODO: Replace with algorithm
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i].Render();
	}
}

