#include "Background.h"

// TODO: Replace GetScreenWidth etc with a playfield rect
Background::Star::Star()
	: position{ static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150)) , static_cast<float>(GetRandomValue(0, GetScreenHeight())) }, size{ static_cast<float>(GetRandomValue(1, 2)) }
{
}

void Background::Star::Render()
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}

Background::Background(size_t starAmount)
	: stars{starAmount}
{
}

void Background::Render()
{
	// TODO: Replace with algorithm
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i].Render();
	}
}

