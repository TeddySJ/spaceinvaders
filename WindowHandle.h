#pragma once
#include "raylib.h"
#include <string_view>

class RaylibWindowHandle final
{

public:
	RaylibWindowHandle(int screenWidth, int screenHeight, const std::string_view& title);
	~RaylibWindowHandle();

	RaylibWindowHandle(const RaylibWindowHandle&) = delete;
	RaylibWindowHandle& operator=(const RaylibWindowHandle&) = delete;

	RaylibWindowHandle(RaylibWindowHandle&&) = delete;
	RaylibWindowHandle& operator=(RaylibWindowHandle&&) = delete;

	void SetTargetFPS(int fps) const noexcept;
};