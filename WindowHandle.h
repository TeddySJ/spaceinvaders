#pragma once
#include "raylib.h"
#include <string_view>

class RaylibWindowHandle
{

public:
	RaylibWindowHandle(int screenWidth, int screenHeight, const std::string_view& title);
	~RaylibWindowHandle();

	RaylibWindowHandle(const RaylibWindowHandle&) = delete;
	RaylibWindowHandle& operator=(const RaylibWindowHandle&) = delete;

	RaylibWindowHandle(RaylibWindowHandle&&) = default;
	RaylibWindowHandle& operator=(RaylibWindowHandle&&) = default;

	void SetTargetFPS(int fps) const;
};