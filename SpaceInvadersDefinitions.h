#pragma once
#include "raylib.h"

namespace SpaceInvaderUtils
{
	constexpr double target_frame_rate = 60;
	constexpr double target_time_per_frame = 1 / target_frame_rate;

	template <class T, class R>
	static inline auto IsInRange(T value, R min, R max)
	{
		return value >= min && value <= max;
	}

	inline auto GetPlayfieldRectangle()
	{
		return Rectangle{ 0,0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };
	}

	inline auto RectLeft(Rectangle r) { return r.x; }
	inline auto RectRight(Rectangle r) { return r.x + r.width; }
	inline auto RectTop(Rectangle r) { return r.y; }
	inline auto RectBottom(Rectangle r) { return r.y + r.height; }
	inline auto RectCenter(Rectangle r) { return Vector2{ r.x + r.width / 2, r.y + r.height / 2 }; }
}