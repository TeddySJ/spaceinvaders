#pragma once
#include <stdexcept>

class HighscoreSaveException final : public std::runtime_error
{
public:
	[[gsl::suppress(26447)]] // 26447 warns that std::runtime_error is NOT noexcept, but it might as well be, as a throw inside a throw is an unrecoverable failure
	HighscoreSaveException() noexcept
		: std::runtime_error("Failed to create file to store the highscores") {}
};

class RaylibWindowCreationError final : public std::runtime_error
{
public:
	[[gsl::suppress(26447)]] // 26447 warns that std::runtime_error is NOT noexcept, but it might as well be, as a throw inside a throw is an unrecoverable failure
	RaylibWindowCreationError() noexcept
		: std::runtime_error("Failed to create Raylib window") {}
};

class RaylibTextureCreationError final : public std::runtime_error
{
public:
	explicit RaylibTextureCreationError(std::string_view path)
		: std::runtime_error(path.data()) {}
};
