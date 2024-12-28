#include "Background.h"
#include <ranges>

Background::Star::Star() noexcept
	: position{ static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150)) , static_cast<float>(GetRandomValue(0, GetScreenHeight())) }, size{ static_cast<float>(GetRandomValue(1, 2)) }
{
}

void Background::Star::Render() const noexcept
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}

Background::Background(size_t starAmount) noexcept
	: stars{starAmount}
{
}

void Background::Render() const noexcept
{
	for (const auto& star : stars)
	{
		star.Render();
	}
}

