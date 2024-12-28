#pragma once
#include <stdexcept>

class HighscoreSaveException final : public std::runtime_error
{
public:
	HighscoreSaveException()
		: std::runtime_error("Failed to create file to store the highscores") {}
};

class RaylibWindowCreationError final : public std::runtime_error
{
public:
	RaylibWindowCreationError()
		: std::runtime_error("Failed to create Raylib window") {}
};

class RaylibTextureCreationError final : public std::runtime_error
{
public:
	explicit RaylibTextureCreationError(std::string_view path)
		: std::runtime_error(path.data()) {}
};