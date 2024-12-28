#pragma once
#include "raylib.h"

constexpr double target_frame_rate = 60;
constexpr double target_time_per_frame = 1 / target_frame_rate;

template <class T, class R>
auto IsInRange(T value, R min, R max)
{
	return value >= min && value <= max;
}

static inline Rectangle GetTextureBoundsAsRectangle(Texture2D texture)
{
	return {0,0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
}


