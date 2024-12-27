#pragma once
#include <string>

struct HighscoreEntry
{
	static constexpr uint8_t NAME_MAX_LENGTH = 9;

	static constexpr bool IsValidHighscoreInput(int key)
	{
		return key >= 32 && key <= 125;
	}

	std::string name;
	int score;
};
