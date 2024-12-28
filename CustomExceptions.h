#pragma once
#include <stdexcept>

class HighscoreSaveException : public std::runtime_error
{
public:
	HighscoreSaveException()
		: std::runtime_error("Failed to create file to store the highscores") {}
};

class RaylibWindowCreationError : public std::runtime_error
{
public:
	RaylibWindowCreationError()
		: std::runtime_error("Failed to create Raylib window") {}
};

class RaylibTextureCreationError : public std::runtime_error
{
public:
	explicit RaylibTextureCreationError(std::string_view path)
		: std::runtime_error(path.data()) {}
};