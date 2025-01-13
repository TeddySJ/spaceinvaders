#pragma once
#include "raylib.h"

namespace SpaceInvaderUtils
{
	constexpr double target_frame_rate = 60;
	constexpr double target_time_per_frame = 1 / target_frame_rate;

	template <class T, class R>
	constexpr auto IsInRange(T value, R min, R max) noexcept
	{
		return value >= min && value <= max;
	}

	inline auto GetPlayfieldRectangle() noexcept
	{
		return Rectangle{ 0,0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };
	}

	constexpr auto RectLeft(Rectangle r) noexcept { return r.x; }
	constexpr auto RectRight(Rectangle r) noexcept { return r.x + r.width; }
	constexpr auto RectTop(Rectangle r) noexcept { return r.y; }
	constexpr auto RectBottom(Rectangle r) noexcept { return r.y + r.height; }
	constexpr auto RectCenter(Rectangle r) noexcept { return Vector2{ r.x + r.width / 2, r.y + r.height / 2 }; }

}